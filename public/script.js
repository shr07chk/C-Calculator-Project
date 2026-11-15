const expressionEl = document.getElementById('expression');
const resultEl = document.getElementById('result');
const statusEl = document.getElementById('status');
const historyEl = document.getElementById('history');
const angleToggle = document.getElementById('angleToggle');
let expression = '';
let angle = 'DEG';
let history = [];

function render() {
  expressionEl.textContent = expression || '0';
}
function insert(value) {
  expression += value;
  render();
  statusEl.textContent = 'READY';
}
function clearAll() {
  expression = '';
  resultEl.textContent = '0';
  statusEl.textContent = 'READY';
  render();
}
function deleteLast() {
  expression = expression.slice(0, -1);
  render();
}
function showError(msg) {
  resultEl.textContent = 'Error';
  statusEl.textContent = msg.toUpperCase().slice(0, 30);
}
function renderHistory() {
  if (!history.length) {
    historyEl.innerHTML = '<div class="empty">nothing here yet</div>';
    return;
  }
  historyEl.innerHTML = '';
  history.slice().reverse().forEach(item => {
    const div = document.createElement('button');
    div.className = 'history-item';
    div.innerHTML = `<small>${esc(item.expression)}</small><strong>${esc(item.result)}</strong>`;
    div.addEventListener('click', () => {
      expression = item.result;
      resultEl.textContent = item.result;
      render();
    });
    historyEl.appendChild(div);
  });
}
function esc(s) {
  return String(s).replace(/[&<>"']/g, c => ({'&':'&amp;','<':'&lt;','>':'&gt;','"':'&quot;',"'":'&#39;'}[c]));
}

// math engine
// C WebAssembly calculation engine

const basicOperations = {
  add: 1,
  subtract: 2,
  multiply: 3,
  divide: 4,
  power: 5,
  mod: 6
};

const scientificOperations = {
  sin: 1,
  cos: 2,
  tan: 3,
  asin: 4,
  acos: 5,
  atan: 6,
  sinh: 7,
  cosh: 8,
  tanh: 9,
  sqrt: 10,
  cbrt: 11,
  square: 12,
  cube: 13,
  factorial: 14,
  log: 15,
  ln: 16,
  exp: 17,
  abs: 18,
  reciprocal: 19,
  percent: 20,
  pi: 21,
  e: 22
};

function api(op, a, b = 0) {
  if (!window.Module || !Module.cReady) {
  throw new Error("C calculator is loading");
}

  let result;

  if (basicOperations[op] !== undefined) {
    result = Module.ccall(
      'basic_calc',
      'number',
      ['number', 'number', 'number'],
      [basicOperations[op], a, b]
    );
  } else if (scientificOperations[op] !== undefined) {
    const angleMode = angle === 'DEG' ? 0 : 1;

    result = Module.ccall(
      'scientific_calc',
      'number',
      ['number', 'number', 'number'],
      [scientificOperations[op], a, angleMode]
    );
  } else {
    throw new Error('Unknown operation');
  }

  if (!Number.isFinite(result)) {
    throw new Error('Math error');
  }

  return result;
}
// tokenizer
function tokenize(input) {
  const s = input.replace(/π/g, 'pi').replace(/\be\b/g, 'e').replace(/×/g, '*').replace(/÷/g, '/');
  const tokens = [];
  let i = 0;
  while (i < s.length) {
    if (/\s/.test(s[i])) { i++; continue; }
    if (/[0-9.]/.test(s[i])) {
      let j = i;
      while (j < s.length && /[0-9.]/.test(s[j])) j++;
      const n = Number(s.slice(i, j));
      if (!Number.isFinite(n)) throw new Error('bad number');
      tokens.push({type:'number', value:n}); i=j; continue;
    }
    if (/[a-z]/i.test(s[i])) {
      let j=i; while(j<s.length && /[a-z]/i.test(s[j])) j++;
      const w=s.slice(i,j).toLowerCase();
      if (['pi','e'].includes(w)) tokens.push({type:'constant', value:w});
      else throw new Error('use the buttons for functions');
      i=j; continue;
    }
    if ('+-*/^()%'.includes(s[i])) { tokens.push({type:'operator', value:s[i]}); i++; continue; }
    throw new Error('unexpected character');
  }
  return tokens;
}

function toRpn(tokens) {
  const out=[], stack=[];
  const prec={'u-':4,'^':3,'*':2,'/':2,'%':2,'+':1,'-':1};
  let prev='start';
  for (const t of tokens) {
    if (t.type==='number'||t.type==='constant') { out.push(t); prev='value'; }
    else if (t.value==='(') { stack.push(t); prev='left'; }
    else if (t.value===')') {
      while(stack.length&&stack[stack.length-1].value!=='(') out.push(stack.pop());
      if(!stack.length) throw new Error('mismatched parens');
      stack.pop(); prev='value';
    } else {
      let op=t.value;
      if(op==='-'&&(prev==='start'||prev==='operator'||prev==='left')) op='u-';
      while(stack.length&&stack[stack.length-1].value!=='('&&
        ((op!=='^'&&prec[stack[stack.length-1].value]>=prec[op])||
         (op==='^'&&prec[stack[stack.length-1].value]>prec[op]))) out.push(stack.pop());
      stack.push({type:'operator',value:op}); prev='operator';
    }
  }
  while(stack.length) {
    const t=stack.pop(); if(t.value==='(') throw new Error('mismatched parens'); out.push(t);
  }
  return out;
}

function evalExpr(input) {
  const rpn=toRpn(tokenize(input)), stk=[];
  for(const t of rpn) {
    if(t.type==='number') stk.push(t.value);
    else if(t.type==='constant') stk.push(api(t.value,0));
    else {
      const op=t.value;
      if(op==='u-') { if(!stk.length) throw new Error('bad expression'); stk.push(-stk.pop()); continue; }
      if(stk.length<2) throw new Error('bad expression');
      const b=stk.pop(), a=stk.pop();
      const map={'+':'add','-':'subtract','*':'multiply','/':'divide','^':'power','%':'mod'};
      stk.push(api(map[op],a,b));
    }
  }
  if(stk.length!==1) throw new Error('bad expression');
  return stk[0];
}

function doUnary(op) {
  if (!expression) throw new Error('type a number first');
  const val = evalExpr(expression);
  const result = api(op, val);
  const old = expression;
  const fmt = format(result);
  expression = fmt;
  resultEl.textContent = fmt;
  statusEl.textContent = 'OK';
  history.push({expression: old + ' → ' + op, result: fmt});
  renderHistory(); render();
}

function format(n) {
  if (!Number.isFinite(n)) return 'Error';
  return Number(n.toPrecision(12)).toString();
}

function equals() {
  if (!expression) return;
  const old = expression;
  try {
    const result = evalExpr(old);
    const fmt = format(result);
    resultEl.textContent = fmt;
    statusEl.textContent = 'OK';
    history.push({expression: old, result: fmt});
    if (history.length > 20) history.shift();
    renderHistory();
    expression = fmt;
    render();
  } catch (err) { showError(err.message); }
}

// wire up buttons
document.querySelectorAll('[data-insert]').forEach(btn =>
  btn.addEventListener('click', () => insert(btn.dataset.insert)));

document.querySelectorAll('[data-action]').forEach(btn =>
  btn.addEventListener('click', () => {
    try { doUnary(btn.dataset.action); } catch(e) { showError(e.message); }
  }));

document.querySelectorAll('[data-command]').forEach(btn =>
  btn.addEventListener('click', () => {
    if (btn.dataset.command === 'clear') clearAll();
    if (btn.dataset.command === 'delete') deleteLast();
    if (btn.dataset.command === 'equals') equals();
  }));

angleToggle.addEventListener('click', () => {
  angle = angle === 'DEG' ? 'RAD' : 'DEG';
  angleToggle.textContent = angle;
  document.getElementById('modeLabel').textContent = angle;
});

document.getElementById('clearHistory').addEventListener('click', () => {
  history = [];
  renderHistory();
});

document.addEventListener('keydown', e => {
  if (/^[0-9.+\-*/^()%]$/.test(e.key)) insert(e.key);
  else if (e.key === 'Enter' || e.key === '=') { e.preventDefault(); equals(); }
  else if (e.key === 'Backspace') deleteLast();
  else if (e.key === 'Escape') clearAll();
});

render();
