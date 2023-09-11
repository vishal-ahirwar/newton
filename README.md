# C/C++ CLI Open Source Project
![image](https://github.com/vishal-ahirwar/newton/assets/73791462/b640d23e-b505-4a78-b886-025c1f7c89c2)
![image](https://github.com/vishal-ahirwar/newton/assets/73791462/da27be9d-d6bd-414d-97e5-1cf9d770cfde)
![image](https://github.com/vishal-ahirwar/newton/assets/73791462/d454f5a7-9f67-455f-bdec-41afdbae6bbd)
![image](https://github.com/vishal-ahirwar/newton/assets/73791462/e94b7310-9414-4d6b-95b4-610d33849a06)

### CLI For C/C++ Project Development

# How to build newton & install on your system
### Download zip or clone newton github repo
```
git clone https://github.com/vishal-ahirwar/newton
cd newton
```

If your linux system does not have CMAKE isntall isntalled then it is must to isntall that for next step :

`Like for fedora`

```
sudo dnf install cmake 
```
`For debian based disctros `
```
sudo apt-get install cmake
```
`For arch based`
```
sudo pacman -S cmake
```

After the installation of CMAKE follow the following commands
```
cmake -S . -B build
cd build 
```


### to Compile & install on your system
```
sudo make install
```
# How to use CLI's simple functions
### to create project
```
newton create your-project-name
```
### to compile your project
```
cd your-project
newton compile
```
### to run your project
```
newton run
```
## And Congrates You have done how to use newton CLI
# Thank You for All of the project contributers and Users
```
Copyright©2022 Vishal Ahirwar and Contributers. all rights reserved.
```
