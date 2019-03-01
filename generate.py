import re

from textgenrnn import textgenrnn


class Generate:
    def __init__(self, artist):
        artist = artist.lower()

        if not artist or artist not in ('abba', 'ledin', 'linnros', 'maggio', 'kendrick'):
            return None

        textgen = self.get_textgen(artist)

        out = textgen.generate(
            temperature=self.temperature,
            prefix=None,
            n=10,
            max_gen_length=60,
            return_as_list=True)

        self.set_generated(out)

    temperature = [1.0, 0.5, 0.2, 0.2]
    generated = ''

    def set_generated(self, input_list):
        out = '.\n'.join(
            re.sub(
                r'(^([^\w\dåäöÅÄÖ]){1,})',
                '',
                re.sub(
                    r'([^\w\dåäöÅÄÖ]){1,}$',
                    '',
                    w
                )
            ).capitalize() for w in input_list
        )

        removed_repetition = re.sub(r'\b(\w+)\s+\1\b', r'\1', out)
        removed_commas_and_extras = re.sub(
            r'([\,\"\'\(\)]\s){2,}', r'\1', removed_repetition)
        removed_unneeded_whitespace = re.sub(
            r'\s([^\w\dåäöÅÄÖ])', r'\1', removed_commas_and_extras)

        self.generated = '{}.'.format(removed_unneeded_whitespace)

    def get_file(self, artist):
        weights_path = './models/{}_weights.hdf5'.format(artist)
        vocab_path = './models/{}_vocab.json'.format(artist)
        config_path = './models/{}_config.json'.format(artist)

        return weights_path, vocab_path, config_path

    def get_textgen(self, artist):
        weights_path, vocab_path, config_path = self.get_file(artist)

        return textgenrnn(weights_path=weights_path,
                          vocab_path=vocab_path,
                          config_path=config_path)
