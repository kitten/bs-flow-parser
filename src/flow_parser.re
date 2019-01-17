let parse_options: option(Parser_env.parse_options) = Some({
  esproposal_class_instance_fields: true,
  esproposal_class_static_fields: true,
  esproposal_decorators: true,
  esproposal_export_star_as: true,
  esproposal_optional_chaining: false,
  esproposal_nullish_coalescing: false,
  types: false,
  use_strict: false
});

let parse = content => {
  Parser_flow.program(~fail=true, ~parse_options, content);
};
