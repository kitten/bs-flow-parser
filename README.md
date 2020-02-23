# bs-flow-parser

This is [Flow's](https://github.com/facebook/flow) [parser](https://github.com/facebook/flow/tree/master/src/parser) modified
and packaged for BuckleScript. The changes that have been made are not alterations to how the Flow parser works, but simply
to get it to compile, mostly due to BuckleScript's older version of OCaml.

> NOTE: The most significant alterations can be seen by going back to this repo's commit
> [that adds the original Flow parser source files](https://github.com/kitten/bs-flow-parser/commit/4544435)
> that were needed for the basic parser and lexer.
> A patch file that summarises the changes can be found [here](./patches/flow-parser-0.91.0-to-bs.patch).

Furthermore the modules that will probably interest you as they're the
entrypoint modules, `Flow_parser` and `Flow_parser_js`, are fully
customised.

The entire package is namespaced to `BsFlowParser`. It can be installed from npm:
`yarn add wonka` or `npm install --save wonka`, after which you can add the module to your `bsconfig.json`:

```diff
{
  "name": "<your name>",
  "version": "0.1.0",
  "sources": ["src"],
  "bsc-flags": ["-bs-super-errors"],
  "bs-dependencies": [
+    "bs-flow-parser"
  ]
}
```

> NOTE: If you're looking to use this package in JavaScript, it will work, but it's nonetheless recommended to use the
> official JSoO compiled version [`flow-parser`](https://npmjs.com/package/flow-parser)

A small, non-scientific benchmark can be found [here](./benchmark/README.md), tl;dr performance of the bundled parser
seems to be on par with the JSoO version on npm.
