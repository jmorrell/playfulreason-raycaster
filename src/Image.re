type t;

external make: int => int => t = "Image" [@@bs.new];
external setSrc : t => string => unit = "src" [@@bs.set];
