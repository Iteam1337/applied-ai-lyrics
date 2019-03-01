module Api = {
  open Js.Promise;
  let get_lyrics = (artist: Artist.artist) => {
    Axios.get(
      "http://localhost:5000/api/generate/" ++ Artist.get_endpoint(artist),
    )
    |> then_(response => resolve(response));
  };
};

module Styles = {
  open Emotion;

  let wrap = [%css
    [
      alignItems(`center),
      display(`flex),
      flexDirection(`column),
      position(`absolute),
      bottom(Calc.(`px(32) + `pct(100.))),
      right(`auto),
      left(`px(-6)),
      transform(`scale(0.75)),
      transformOrigin(`pct(0.), `pct(100.)),
      select(
        ":after",
        [
          content(""),
          position(`absolute),
          bottom(`px(-12)),
          left(`px(62)),
          width(`px(24)),
          height(`px(24)),
          backgroundColor(`hex("FF0856")),
          transforms([`rotate(`deg(45.0)), `scale(0.75)]),
        ],
      ),
    ]
  ];

  let wrap_l = [%css
    [
      left(`auto),
      right(`px(-6)),
      transformOrigin(`pct(100.), `pct(100.)),
      select(":after", [right(`px(62)), left(`auto)]),
    ]
  ];
  let wrap_left = Cx.merge([|wrap, wrap_l|]);
};

type state =
  | Error
  | Idle
  | Loading
  | Lyrics(string);

type action =
  | Error
  | Fetch
  | Success(string)
  | Loading;

type retainedProps = {artist: Artist.artist};

let component = ReasonReact.reducerComponentWithRetainedProps(__MODULE__);

let make = (~artist, ~left=false, _children) => {
  ...component,
  retainedProps: {
    artist: artist,
  },

  initialState: () => Idle,

  didMount: self => self.send(Fetch),

  didUpdate: ({oldSelf, newSelf}) =>
    if (oldSelf.retainedProps.artist !== newSelf.retainedProps.artist) {
      newSelf.send(Fetch);
    },

  reducer: (action, _state) =>
    switch (action) {
    | Error => ReasonReact.Update(Error)

    | Fetch =>
      ReasonReact.UpdateWithSideEffects(
        Loading,
        self =>
          Js.Promise.(
            Api.get_lyrics(artist)
            |> then_(res => resolve(self.send(Success(res##data##data))))
            |> catch(_err => resolve(self.send(Error)))
            |> ignore
          ),
      )
    | Loading => ReasonReact.Update(Loading)
    | Success(l) => ReasonReact.Update(Lyrics(l))
    },

  render: ({state}) => {
    <div className={left ? Styles.wrap_left : Styles.wrap}>
      {switch (state) {
       | Idle => "" |> ReasonReact.string
       | Error =>
         {j|Oj. Det verkar som att någonting har gått snett. Ryck tag i en moderator så skall de nog kunna hjälpa till!|j}
         |> ReasonReact.string
       | Loading => <Card artist />
       | Lyrics(lyrics) => <Card lyrics artist />
       }}
    </div>;
  },
};
