<h1 align="center">
  <br />
  Smarty
</h1>

<p align="center">
  A feedforward neural network implementation built completely from scratch
</p>

This is a personal project to write a neural network implementation with backpropogation learning in C++ completely from scratch, without the help of any guides, tutorials or external libraries (even linear algebra ones). The only reference used to write this project was was Wikipedia, mostly [this page](https://en.wikipedia.org/wiki/Backpropagation). 

Currently the network works for feeding forward, i.e. if you assign a network with a given set of weights/hidden layers, it can calculate the output of the network for any given input. Backpropogation based gradient descent learning is also implemented, but has some issues and doesn't quite work. 

<h2 align="center">
  <br />
  Setup
</h2>

To build the project, simply run

```bash
$ make
```

This will generate the ``build/`` directory with the ``main`` executable inside. To run tests run 

```bash
$ ./build/main
```

To debug using gdb, you can simply run

```bash
$ gdb ./build/main
```

Symbols are included by default in the Makefile so you should then be able to debug the c++ program with gdb as usual. 

<h2 align="center">
  <br />
  Code
</h2>

There are two main classes that are used to represent the network. 

```C
class Net{};
```

The ``Net`` class represents a neural network, with a fixed number of hidden layers and weights assigned upon initialization. The ``Net.run(Matrix &input)`` method is used to run the network forward with the given input, while the ``Net.backpropogate`` uses gradient descent and the backprogation algorithm to train the network with a given input/output pair with a given learning rate. 

```C
class Matrix{};
```

The ``Matrix`` class is used to represent both matrices and vectors. They are not dynamically scalable. Most common operations are implemented, such as matrix multiplication, Hadamard product, scalar multiplication and addition. Column vectors are represented by Nx1 matrices, where N is their length. This does introduce some inefficiencies since there's an extra layer of dynamically allocated pointer indirection that isn't needed, but at least for now more than makes up for that by not having duplicated/messier code. 

See ``test/main.cpp`` for implementations of both of these classes and how they are to be used. 



