open Emotion;

let button = [%css
  [
    alignItems(`center),
    appearance(`none),
    backgroundColor(`hex("FF0856")),
    borderRadius(`px(5)),
    boxShadow(~y=px(8), ~blur=px(32), `hsla((341, 100, 12, 0.28))),
    color(`hex("FFF")),
    cursor(`pointer),
    display(`flex),
    fontSize(`px(18)),
    height(`px(48)),
    justifyContent(`center),
    width(`px(164)),
  ]
];