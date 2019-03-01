module Styles = {
  open Emotion;

  let avatar = [%css
    [
      appearance(`none),
      borderRadius(`px(96)),
      borderWidth(`px(0)),
      boxShadow(~y=px(4), ~blur=px(12), `hsla((341, 100, 12, 0.05))),
      cursor(`pointer),
      height(`px(96)),
      marginLeft(`px(25)),
      marginRight(`px(25)),
      outlineStyle(`none),
      transitionDuration(`ms(150)),
      transitionProperty("box-shadow transform"),
      transitionTimingFunction(`easeIn),
      position(`relative),
      padding(`px(0)),
      width(`px(96)),
      hover([
        boxShadow(~y=px(4), ~blur=px(12), `hsla((341, 100, 12, 0.1))),
      ]),
    ]
  ];

  let avatar_s = [%css
    [
      boxShadow(~y=px(4), ~blur=px(16), `hsla((341, 100, 12, 0.12))),
      transform(`scale(1.33)),
    ]
  ];

  let artist_image = [%css
    [width(`px(96)), height(`px(96)), borderRadius(`px(96))]
  ];
  let avatar_selected = Cx.merge([|avatar, avatar_s|]);

  let relative = [%css [position(`relative)]];
};

let component = ReasonReact.statelessComponent(__MODULE__);

let make =
    (~artist: Artist.artist, ~onClick, ~selected, ~left=false, _children) => {
  ...component,

  render: _self => {
    switch (selected) {
    | `Selected =>
      <div className=Styles.relative>
        <button className=Styles.avatar_selected onClick>
          <Lyrics artist left />
          <img
            src={Artist.get_image(artist)}
            alt={Artist.get_name(artist)}
            className=Styles.artist_image
          />
        </button>
      </div>
    | `Not_selected =>
      <div>
        <button className=Styles.avatar onClick>
          <img
            src={Artist.get_image(artist)}
            alt={Artist.get_name(artist)}
            className=Styles.artist_image
          />
        </button>
      </div>
    };
  },
};
