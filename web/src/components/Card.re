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

  let l = [%css [width(`px(128))]];
  let loader = Cx.merge([|holder, l|]);
};

let component = ReasonReact.statelessComponent(__MODULE__);

let make = (~artist, ~lyrics=?, _children) => {
  ...component,

  render: _self => {
    let artist_name = artist |> Artist.get_name;

    let hasLyrics = Belt.Option.isSome(lyrics);

    <div className={hasLyrics ? Styles.holder : Styles.loader}>
      <div className=Styles.text>
        {if (hasLyrics) {
           <div>
             {Belt.Option.getWithDefault(lyrics, "") |> ReasonReact.string}
             <span className=Styles.artist>
               {{j|– $artist_name ITEAM |j} |> ReasonReact.string}
             </span>
           </div>;
         } else {
           ReasonReact.string("Loading...");
         }}
      </div>
    </div>;
  },
};
