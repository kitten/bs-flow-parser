[@bs.new] external createRegex : (string, string) => _ = "RegExp";

module JsTranslator: {
  let translation_errors: ref(list((Loc.t, Parse_error.t)));
  include Translator_intf.S;
} = {
  type t = Js.Json.t;

  let translation_errors = ref([]);
  let string = Json.Encode.string;
  let bool = Json.Encode.bool;
  let obj = Json.Encode.object_;
  let array = arr => Json.Encode.jsonArray(Array.of_list(arr));
  let number = Json.Encode.float;
  let null = Json.Encode.null;

  let regexp = (loc, pattern, flags) => {
    try (createRegex(pattern, flags)) {
    | _ =>
      translation_errors := [(loc, Parse_error.InvalidRegExp), ...translation_errors^];
      createRegex("", flags);
    }
  };
};

module Translate = Estree_translator.Translate(
  JsTranslator,
  {
    let include_comments = true;
    let include_locs = true;
  }
);

module Token_translator = Token_translator.Translate(JsTranslator);

let parse = (content, _options) => {
  let (ocaml_ast, _errors) = Parser_flow.program(~fail=false, ~parse_options=None, content);
  JsTranslator.translation_errors := [];
  let offset_table = Offset_utils.make(content);
  Translate.program(Some(offset_table), ocaml_ast)
};
