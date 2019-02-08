
from textgenrnn import textgenrnn

textgen = textgenrnn(weights_path='./models/ledin_weights.hdf5',
                       vocab_path='./models/ledin_vocab.json',
                       config_path='./models/ledin_config.json')

# this temperature schedule cycles between 1 very unexpected token, 1 unexpected token, 2 expected tokens, repeat.
# changing the temperature schedule can result in wildly different output!
temperature = [1.0, 0.5, 0.2, 0.2]   
prefix = None   # if you want each generated text to start with a given seed text

textgen.generate(
  temperature=temperature,
  prefix=prefix,
  n=1000,
  max_gen_length=60)

#textgen = textgenrnn('textgenrnn_weights.hdf5')
# textgen = textgenrnn(name="eminem")
# textgen.reset()
# textgen.train_from_file('./lyrics/eminem.txt', 
#  word_level=False,
#  rnn_bidirectional=True,
#  num_epochs=10,
#  max_length=10,
#  max_gen_length=50,
#  max_words=5000)
# textgen.generate(10, temperature=0.7, prefix="")