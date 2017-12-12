## Libraries
### GSL
Pleaes install the GSL Scientific Library before using this program.  
Mac:  
http://connor-johnson.com/2014/10/12/using-the-gnu-scientific-library-on-a-mac/  
Ubuntu:  
https://askubuntu.com/questions/490465/install-gnu-scientific-library-gsl-on-ubuntu-14-04-via-terminal  

## Training
Plase follow the following steps for training your own model.  
1. Edit **train/Makefile** so that it contains the right GSL library path as installed on your machine.
2. Put training images of size **20x20 pixels** in the **training_set/** folder. 
The images can be in either **.jpg** or **".png"** format. Name the images in sequence with increasing numbers.
For example, name the first training image as **0.jpg** and second one as **1.jpg**.
3. Run **mkdir models** and **mkdir data** under the project directory.
4. Run **train/prepTrainingSet.sh**
5. Run **mkdir build** inside **train/** folder.
6. Run **make** inside **train/** folder.
7. cd into **train/build/** and run the built binary **train**.
8. The trained models can be found as txt files under **models/** folder.

## Face Recognition
Please follow the following steps for using the program to recognize a face image.
1. Put an image in either **.jpg** or **.png** format inside the **input/** folder. The width and height 
of the image should both be at least **20px**.
2. Run **prepInput.sh** under the project directory.
3. Run **mkdir build** under the project directory.
4. Run **make** under the project directory.
5. cd into **build/** and run the built binary **main**.
6. The program will output the index of the trained images, ordered by numbers 
in their names, that is closest to the input image.
