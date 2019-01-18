module JsTranslator: Translator_intf.S = {
  type t = Js.Json.t;

  let string = Json_encode.string;
  let bool = Json_encode.bool;
  let obj = Json_encode.obj;
  let array = arr => Json_encode.jsonArray(Array.of_list(arr));
  let number = Json_encode.float;
  let null = Json_encode.null;

  let regexp = (_loc, pattern, flags) => {
    try (Json_encode.regexp(pattern, flags)) {
    | _ => Json_encode.regexp("", flags)
    }
  };
};

module Translate = Estree_translator.Translate(
  JsTranslator,
  {
    let include_comments = false;
    let include_locs = true;
  }
);

module Token_translator = Token_translator.Translate(JsTranslator);

type options = Js.t({.
  esproposal_class_instance_fields: bool,
  esproposal_class_static_fields: bool,
  esproposal_decorators: bool,
  esproposal_export_star_as: bool,
  esproposal_optional_chaining: bool,
  esproposal_nullish_coalescing: bool,
  types: bool,
  use_strict: bool
});

let parse = (content: string, options: option(options)) => {
  open Parser_env;

  let parse_options = switch (options) {
  | Some(opt) => Some({
    esproposal_class_instance_fields: opt##esproposal_class_instance_fields,
    esproposal_class_static_fields: opt##esproposal_class_static_fields,
    esproposal_decorators: opt##esproposal_decorators,
    esproposal_export_star_as: opt##esproposal_export_star_as,
    esproposal_optional_chaining: opt##esproposal_optional_chaining,
    esproposal_nullish_coalescing: opt##esproposal_nullish_coalescing,
    types: opt##types,
    use_strict: opt##use_strict
  })
  | None => None
  };

  let (ocaml_ast, _errors) = Parser_flow.program(~fail=false, ~parse_options, content);
  let offset_table = Offset_utils.make(content);
  Translate.program(Some(offset_table), ocaml_ast)
};
