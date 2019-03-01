type artist =
  | Abba
  | Kendrick
  | Ledin
  | Linnros
  | Maggio;

type t = {name: string};

let get_name = artist =>
  switch (artist) {
  | Abba => "Abba"
  | Kendrick => "Kendrick Lamar"
  | Ledin => "Tomas Ledin"
  | Linnros => "Oskar Linnros"
  | Maggio => "Veronica Maggio"
  };

let get_endpoint = artist => {
  switch (artist) {
  | Abba => "abba"
  | Kendrick => "kendrick"
  | Ledin => "ledin"
  | Linnros => "linnros"
  | Maggio => "maggio"
  };
};

/**
 * TODO(@lessp): Add avatar image support
 */

let get_image = artist => "./img/" ++ get_endpoint(artist) ++ ".png";

let get_all = () => [Abba, Kendrick, Ledin, Linnros, Maggio];
