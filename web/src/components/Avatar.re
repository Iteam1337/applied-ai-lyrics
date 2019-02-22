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
      /***
       * TODO(@lessp): Add this
       */
      /* <img src={Artist.get_image(artist)} alt={Artist.get_name(artist)} /> */
       {Artist.get_name(artist) |> ReasonReact.string} </button>;
  },
};