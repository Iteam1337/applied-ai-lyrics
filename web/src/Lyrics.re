module Api = {
  open Js.Promise;
  let get_lyrics = (artist: Artist.artist) => {
    Axios.get(
      "http://localhost:5000/api/generate/" ++ Artist.get_endpoint(artist),
    )
    |> then_(response => resolve(response));
  };
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

let make = (~artist, _children) => {
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

  render: self => {
    <div className=Styles.lyrics_wrap>
      {switch (self.state) {
       | Idle => ReasonReact.string("")
       | Error =>
         ReasonReact.string(
           "Oj. Det verkar som att någonting har gått snett. Ryck tag i en moderator så skall de nog kunna hjälpa till!",
         )
       | Loading => ReasonReact.string("Loading...")
       | Lyrics(lyrics) => <Card lyrics artist />
       }}
    </div>;
  },
};