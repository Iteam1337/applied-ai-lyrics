let component = ReasonReact.statelessComponent(__MODULE__);

let make = (~artist: Artist.artist, ~onClick, ~selected, _children) => {
  ...component,

  render: _self => {
    let style =
      switch (selected) {
      | `Selected => Styles.artist_avatar_selected
      | `Not_selected => Styles.artist_avatar
      };

    <button className=style onClick>
      {Artist.get_name(artist) |> ReasonReact.string}
    </button>;
  },
};