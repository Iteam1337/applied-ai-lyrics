module Styles = {
  open Emotion;

  let holder = [%css
    [
      backgroundColor(`hex("FF0856")),
      borderRadius(`px(24)),
      boxShadow(~y=px(8), ~blur=px(32), `hsla((341, 100, 12, 0.28))),
      color(`hex("FFF")),
      display(`flex),
      fontSize(`px(18)),
      fontStyle(`italic),
      lineHeight(`pct(150.)),
      marginTop(`px(25)),
      width(`px(512)),
      textAlign(`left),
    ]
  ];

  let text = [%css [padding(`px(25))]];

  let l = [%css [width(`px(128))]];
  let loader = Cx.merge([|holder, l|]);
};

let component = ReasonReact.statelessComponent(__MODULE__);

let make = (~is_small=false, children) => {
  ...component,

  render: _self => {
    <div className={is_small ? Styles.loader : Styles.holder}>
      <div className=Styles.text> ...children </div>
    </div>;
  },
};