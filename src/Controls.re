
open Bs_webapi.Dom;

/* Magic event translation functions */
external eventToKeyboardEvent : Dom.event => KeyboardEvent.t = "%identity";
external eventToTouchEvent : Dom.event => TouchEvent.t = "%identity";

type states = {
  left: bool,
  right: bool,
  forward: bool,
  backward: bool,
};

type t = ref states;

type direction = Left | Right | Forward | Backward;

let empty = { left: false, right: false, forward: false, backward: false };

let getCode keyCode => {
  switch (keyCode) {
  | "ArrowUp" => Some Forward
  | "ArrowLeft" => Some Left
  | "ArrowRight" => Some Right
  | "ArrowDown" => Some Backward
  | _ => None
  };
};

let updateState controls value direction => {
  switch (direction) {
  | Some Left => controls := {...(!controls), left: value }
  | Some Forward => controls := {...(!controls), forward: value }
  | Some Backward => controls := {...(!controls), backward: value }
  | Some Right => controls := {...(!controls), right: value }
  | None => ()
  };
};

let onKey controls value e => {
  Event.preventDefault e;
  Event.stopPropagation e;
  let direction = e |> eventToKeyboardEvent |> KeyboardEvent.code |> getCode;
  updateState controls value direction;
};

let onTouch controls e => {
  controls := empty;
  Event.preventDefault e;
  Event.stopPropagation e;
  /* TODO: Bs_webapi doesn't have support for getting touch event info yet */
  let _touches = TouchEvent.touches (eventToTouchEvent e);
};

let onTouchEnd controls e => {
  controls := empty;
  Event.preventDefault e;
  Event.stopPropagation e;
};

let make _ => {
  let controls = ref empty;
  Document.addEventListener "keydown" (onKey controls true) document;
  Document.addEventListener "keyup" (onKey controls false) document;
  Document.addEventListener "touchstart" (onTouch controls) document;
  Document.addEventListener "touchmove" (onTouch controls) document;
  Document.addEventListener "touchend" (onTouchEnd controls) document;
  controls;
};

let getStates controls => {
  [%bs.obj {
    left: (!controls).left,
    right: (!controls).right,
    forward: (!controls).forward,
    backward: (!controls).backward,
  } ];
};
