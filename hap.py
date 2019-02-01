
from textgenrnn import textgenrnn

textgen = textgenrnn(weights_path='./models/ledin_weights.hdf5',
                       vocab_path='./models/ledin_vocab.json',
                       config_path='./models/ledin_config.json')

textgen.generate_to_file("test.txt",n=50, temperature=[1.0, 0.5, 0.2, 0.2], max_gen_length=60)

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