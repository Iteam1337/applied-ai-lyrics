from textgenrnn import textgenrnn

class Generate:
    def __init__(self, artist):
      textgen = self.get_textgen(artist)

      out = textgen.generate(
        temperature=self.temperature,
        prefix=None,
        n=20,
        max_gen_length=60,
        return_as_list=True)

      textgen = None

      self.generated = " ".join(out)

    temperature = [1.0, 0.5, 0.2, 0.2]
    generated = ''

    def get_file(self, artist):
      weights_path = './models/{}_weights.hdf5'.format(artist)
      vocab_path = './models/{}_vocab.json'.format(artist)
      config_path = './models/{}_config.json'.format(artist)

      return weights_path, vocab_path, config_path

    def get_textgen(self, artist):
      weights_path, vocab_path, config_path = self.get_file(artist)

      return textgenrnn(weights_path = weights_path,
                        vocab_path = vocab_path,
                        config_path = config_path)