
from textgenrnn import textgenrnn

model_name = 'abba'
weights_path = './models/{}_weights.hdf5'.format(model_name)
vocab_path = './models/{}_vocab.json'.format(model_name)
config_path = './models/{}_config.json'.format(model_name)

textgen = textgenrnn(weights_path = weights_path,
                       vocab_path = vocab_path,
                       config_path = config_path)

# this temperature schedule cycles between 1 very unexpected token, 1 unexpected token, 2 expected tokens, repeat.
# changing the temperature schedule can result in wildly different output!
temperature = [1.0, 0.5, 0.2, 0.2]   
prefix = None   # if you want each generated text to start with a given seed text

textgen.generate(
  temperature=temperature,
  prefix=prefix,
  n=100,
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