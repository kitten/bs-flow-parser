const { readFileSync } = require('fs');
const bsParse = require('..').parse;
const jsooParse = require('flow-parser').parse;

const contents = readFileSync('./stylis.js', { encoding: 'utf8' });

suite('flow-parser', () => {
  benchmark('jsoo', () => {
    jsooParse(contents);
  });

  benchmark('bs', () => {
    bsParse(contents);
  });
});
