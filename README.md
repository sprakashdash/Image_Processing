# Image_Processing
Image Processing Workshop at IIT KHARAGPUR

## Installation of OpenCV3 on Ubuntu:

  ### Step 1: Update packages
  ```
    sudo apt-get update
    sudo apt-get upgrade
  ```
  ### Step 2: Install OS libraries
  ```
    #Remove any previous installations of x264</h3>
    sudo apt-get remove x264 libx264-dev
  ```
  ```
    #We will Install dependencies now
    sudo apt-get install build-essential checkinstall cmake pkg-config yasm
    sudo apt-get install git gfortran
    sudo apt-get install libjpeg8-dev libjasper-dev libpng12-dev
  ```
  ```
    # If you are using Ubuntu 14.04
    sudo apt-get install libtiff4-dev
    # If you are using Ubuntu 16.04
    sudo apt-get install libtiff5-dev
  ```
  ```
    sudo apt-get install libavcodec-dev libavformat-dev libswscale-dev libdc1394-22-dev
    sudo apt-get install libxine2-dev libv4l-dev
    sudo apt-get install libgstreamer0.10-dev libgstreamer-plugins-base0.10-dev
    sudo apt-get install qt5-default libgtk2.0-dev libtbb-dev
    sudo apt-get install libatlas-base-dev
    sudo apt-get install libfaac-dev libmp3lame-dev libtheora-dev
    sudo apt-get install libvorbis-dev libxvidcore-dev
    sudo apt-get install libopencore-amrnb-dev libopencore-amrwb-dev
    sudo apt-get install x264 v4l-utils
  ```
  ```
    # Optional dependencies
    sudo apt-get install libprotobuf-dev protobuf-compiler
    sudo apt-get install libgoogle-glog-dev libgflags-dev
    sudo apt-get install libgphoto2-dev libeigen3-dev libhdf5-dev doxygen
  ```
  ### Step 3: Install Python libraries
  ```
    sudo apt-get install python-dev python-pip python3-dev python3-pip
    sudo -H pip2 install -U pip numpy
    sudo -H pip3 install -U pip numpy
  ```
  ```
    # Install virtual environment
    sudo pip2 install virtualenv virtualenvwrapper
    sudo pip3 install virtualenv virtualenvwrapper
    echo "# Virtual Environment Wrapper"  >> ~/.bashrc
    echo "source /usr/local/bin/virtualenvwrapper.sh" >> ~/.bashrc
    source ~/.bashrc
  ```
  ```
    ############ For Python 2 ############
    # create virtual environment
    mkvirtualenv facecourse-py2 -p python2
    workon facecourse-py2

    # now install python libraries within this virtual environment
    pip install numpy scipy matplotlib scikit-image scikit-learn ipython

    # quit virtual environment
    deactivate
    ######################################

    ############ For Python 3 ############
    # create virtual environment
    mkvirtualenv facecourse-py3 -p python3
    workon facecourse-py3

    # now install python libraries within this virtual environment
    pip install numpy scipy matplotlib scikit-image scikit-learn ipython

    # quit virtual environment
    deactivate
    ######################################
 ```
### Step 4: Download OpenCV and OpenCV_contrib
 
 **Step 4.1: Download opencv from Github**
  ```
    git clone https://github.com/opencv/opencv.git
    cd opencv 
    git checkout 3.3.1 
    cd ..
  ```
  **Step 4.2: Download opencv_contrib from Github**
  ```  
    git clone https://github.com/opencv/opencv_contrib.git
    cd opencv_contrib
    git checkout 3.3.1
    cd ..
  ```
### Step 5: Compile and install OpenCV with contrib modules

  **Step 5.1: Create a build directory**
  ```  
    cd opencv
    mkdir build
    cd build
  ```
  **Step 5.2: Run CMake**
  ```
    cmake -D CMAKE_BUILD_TYPE=RELEASE \
      -D CMAKE_INSTALL_PREFIX=/usr/local \
      -D INSTALL_C_EXAMPLES=ON \
      -D INSTALL_PYTHON_EXAMPLES=ON \
      -D WITH_TBB=ON \
      -D WITH_V4L=ON \
      -D WITH_QT=ON \
      -D WITH_OPENGL=ON \
      -D OPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules \
      -D BUILD_EXAMPLES=ON ..
   ``` 
  **Step 5.3: Compile and Install**
  ```
    # find out number of CPU cores in your machine
    nproc
    # substitute 4 by output of nproc
    make -j4
    sudo make install
    sudo sh -c 'echo "/usr/local/lib" >> /etc/ld.so.conf.d/opencv.conf'
    sudo ldconfig
  ```
  **Step 5.4: Create symlink in virtual environment**
  
  Depending upon Python version you have, paths would be different. 
  OpenCV’s Python binary (cv2.so) can be installed either in directory site-packages or dist-packages. 
  Use the following command to find out the correct location on your machine.
  ```
    find /usr/local/lib/ -type f -name "cv2*.so"
  ```
  It should output paths similar to one of these (or two in case OpenCV was compiled for both Python2 and Python3):
  ```  
    ############ For Python 2 ############
    ## binary installed in dist-packages
    /usr/local/lib/python2.6/dist-packages/cv2.so
    /usr/local/lib/python2.7/dist-packages/cv2.so
    ## binary installed in site-packages
    /usr/local/lib/python2.6/site-packages/cv2.so
    /usr/local/lib/python2.7/site-packages/cv2.so

    ############ For Python 3 ############
    ## binary installed in dist-packages
    /usr/local/lib/python3.5/dist-packages/cv2.cpython-35m-x86_64-linux-gnu.so
    /usr/local/lib/python3.6/dist-packages/cv2.cpython-36m-x86_64-linux-gnu.so
    ## binary installed in site-packages
    /usr/local/lib/python3.5/site-packages/cv2.cpython-35m-x86_64-linux-gnu.so
    /usr/local/lib/python3.6/site-packages/cv2.cpython-36m-x86_64-linux-gnu.so
  ```  
  Double check the exact path on your machine before running the following commands
  ```
    ############ For Python 2 ############
    cd ~/.virtualenvs/facecourse-py2/lib/python2.7/site-packages
    ln -s /usr/local/lib/python2.7/dist-packages/cv2.so cv2.so

    ############ For Python 3 ############
    cd ~/.virtualenvs/facecourse-py3/lib/python3.6/site-packages
    ln -s /usr/local/lib/python3.6/dist-packages/cv2.cpython-36m-x86_64-linux-gnu.so cv2.so
  ```  
## Running OpenCV codes

  **In C++:**
  ```
    g++ filename.cpp `pkg-config --cflags --libs opencv`
    ./a.out
  ```  
  **In python:**
  ```
    ############ For Python 2 ############
    workon facecourse-py2
    ############ For Python 3 ############
    workon facecourse-py3
    
    python filename.py
    
    deactivate
  ```
