var path = require('path');

module.exports = {
  name: 'BsFlowParser',
  mode: 'production',
  entry: './lib/js/src/js/flow_parser_js.js',
  performance: {
    hints: false
  },
  output: {
    path: path.resolve(__dirname, 'dist'),
    filename: 'flow_parser.bundle.js',
    libraryTarget: 'commonjs'
  }
};
