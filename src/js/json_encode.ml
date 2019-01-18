 external regexp : string -> string -> _ = "RegExp" [@@bs.new]

external string : string -> Js.Json.t = "%identity"
external bool : bool -> Js.Json.t = "%identity"
external float : float -> Js.Json.t = "%identity"
external dict : Js.Json.t Js_dict.t -> Js.Json.t = "%identity"
external null : Js.Json.t = "" [@@bs.val]
external jsonArray : Js.Json.t array -> Js.Json.t = "%identity"

let obj props: Js.Json.t =
  props |> Js.Dict.fromList
        |> dict
