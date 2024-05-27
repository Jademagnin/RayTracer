# Raytracer
The Raytracer project is a collaborative effort aiming to create a ray tracing engine using modern programming techniques.  
The project focuses on implementing various features such as different materials, lighting models, and geometries.  
This project was carried out by jade.magnin@epitech.eu and nathanael.moehn@epitech.eu.

## Engine Features
The ray tracing engine supports various features:

Different geometries: The engine can render different geometric shapes : sphere, plane, cone and cylinder.  
Materials: The engine supports different materials, each with its own light reflection characteristics like Lambertian, Dielectric or Metal.  
Texture : The shapes support different textures like chessboard, image or noise.  
Lighting: The engine supports different lighting models, including diffuse lighting or directional.  
Image rendering: The engine renders the scene into an image with a specified width and height. See image_width and image_height in Camera.

## All features
• Sphere  
• Plane  
• Translation  
• Directional light  
• Ambient light  
• Flat color  
• Add primitives to the scene  
• Set up lighting  
• Set up camera  
• No GUI, output to a PPM file  

• Cylinder  
• Cone  
• Rotation  
• Drop shadows  

• Scale  
• Scene graph  
• Multiple directional lights  
• Multiple point lights  
• Colored light  
• Phong reflection model  
• Ambient occlusion  
• Transparency  
• Refraction  
• Reflection  
• Texturing from file  
• Texturing from a procedural generation of a chessboard  
• Texturing from a procedural generation of Perlin noise  
• Import a scene in a scene  
• Set up antialiasing through supersampling  
• Set up antialiasing through adaptative supersampling  
• Space partitioning  
• Multithreading  
• Clustering

• Density  
• Metal  
• Dielectric  
• Isotropic  
• Box  
• Sphere box  
• Time estimation and percentages  

## Dependencies
- SFML
```bash
sudo apt install -y libsfml-dev
```

- Libconfig
```bash
sudo apt install -y libconfig-dev libconfig++-dev
```

## Usage
```bash
git clone git@github.com:EpitechPromo2027/B-OOP-400-STG-4-1-raytracer-jade.magnin.git raytracer
cd raytracer
```

```bash
cmake .
make
```

## Run
```bash
./raytracer > image.ppm
```

## Contributing
Contributions are always welcome! If you encounter any bugs, have suggestions for improvements, or would like to contribute additional features, please feel free to submit a pull request.  
You can add a feature on the corresponding folder and add a .config for run scene of your choice.

## License
This project is licensed under the MIT License, which means you are free to use, modify, and distribute the code as long as you include the original copyright and license notice.
