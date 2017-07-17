
open Bs_webapi;

type t = {
  lastTime: float,
  callback: (float => unit),
};

let make lastTime callback => { lastTime, callback };

let rec frame loop time => {
  let seconds = (time -. loop.lastTime) /. 1000.;
  if (seconds < 0.2) {
    loop.callback seconds;
  };
  let newLoop = make time loop.callback;
  requestAnimationFrame (frame newLoop);
};

let start callback => {
  let loop = make 0. callback;
  requestAnimationFrame (frame loop);
};
