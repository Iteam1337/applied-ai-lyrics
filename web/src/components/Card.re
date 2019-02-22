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
    ]
  ];

  let text = [%css [padding(`px(25))]];

  let artist = [%css
    [
      color(`hex("FFE5EE")),
      display(`block),
      fontSize(`px(13)),
      fontStyle(`normal),
      fontWeight(700),
      letterSpacing(`px(1)),
      lineHeight(`pct(150.)),
      marginTop(`px(20)),
      textTransform(`uppercase),
    ]
  ];
};

let component = ReasonReact.statelessComponent(__MODULE__);

let make = (~artist, ~lyrics, _children) => {
  ...component,

  render: _self => {
    let artist_name = artist |> Artist.get_name;

    <div className=Styles.holder>
      <div className=Styles.text>
        {lyrics |> ReasonReact.string}
        <span className=Styles.artist>
          {{j|– $artist_name ITEAM |j} |> ReasonReact.string}
        </span>
      </div>
    </div>;
  },
};