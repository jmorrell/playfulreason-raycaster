
type t = {
  image: Image.t,
  width: int,
  height: int,
};

let make src width height => {
  let image = Image.make width height;
  Image.setSrc image src;
  [%bs.obj { image, width, height }];
};
