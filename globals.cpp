#include "globals.h"
#include "building.h"

GLOBAL_SETTINGS::GLOBAL_SETTINGS(){
	WINDOW_MAX_X = 1000;
	WINDOW_MAX_Y = 1000;

	WORLD_COORDINATE_MIN_X = 0.0;
	WORLD_COORDINATE_MAX_X = 1000.0;
	WORLD_COORDINATE_MIN_Y = 0.0;
	WORLD_COORDINATE_MAX_Y = 1000.0;

	CAMERA_POS = {Building::distanceBetweenBuildings/2.0,
	              Building::distanceBetweenBuildings/2.0,
	              2
			};
	CAMERA_LOOK_VECTOR = {0,1,0};
	CAMERA_ANGLE_VERTICAL = 0;
	CAMERA_ANGLE_HORIZONTAL = 90;

	LIGHTS[0].position[0]=0;
	LIGHTS[0].position[1]=0;
	LIGHTS[0].position[2]=0;
	LIGHTS[0].position[3]=1;
	LIGHTS[0].attenuation_linear=0.0001;
	LIGHTS[0].attenuation_quadratic=0.001;
	LIGHTS[0].color_ambient[0]=0.4;
	LIGHTS[0].color_ambient[1]=0.4;
	LIGHTS[0].color_ambient[2]=0.4;
	LIGHTS[0].color_ambient[3]=1.0;
	LIGHTS[0].color_diffuse[0]=1.0;
	LIGHTS[0].color_diffuse[1]=1.0;
	LIGHTS[0].color_diffuse[2]=1.0;
	LIGHTS[0].color_diffuse[3]=1.0;
	LIGHTS[0].color_specular[0]=0.01;
	LIGHTS[0].color_specular[1]=0.01;
	LIGHTS[0].color_specular[2]=0.01;
	LIGHTS[0].color_specular[3]=1.0;
	LIGHTS[0].spotlight_direction[0] = -1.0;
	LIGHTS[0].spotlight_direction[1] = -0.01;
	LIGHTS[0].spotlight_direction[2] = -0.1;


	LIGHTS[1].position[0] = 0.0;
	LIGHTS[1].position[1] = 0.0;
	LIGHTS[1].position[2] = 1000.0;
	LIGHTS[1].position[3] = 0.0;
    LIGHTS[1].color_ambient[0] = 0.0;
    LIGHTS[1].color_ambient[1] = 0.0;
    LIGHTS[1].color_ambient[2] = 0.0;
    LIGHTS[1].color_ambient[3] = 1.0;
    LIGHTS[1].color_diffuse[0] = 0.9;
    LIGHTS[1].color_diffuse[1] = 0.9;
    LIGHTS[1].color_diffuse[2] = 0.9;
    LIGHTS[1].color_diffuse[3] = 1.0;
    LIGHTS[1].color_specular[0] = 0.1;
    LIGHTS[1].color_specular[1] = 0.1;
    LIGHTS[1].color_specular[2] = 0.1;
    LIGHTS[1].color_specular[3] = 1.0;
    LIGHTS[1].attenuation_linear=0.0001;
	LIGHTS[1].attenuation_quadratic=0.001;
	LIGHTS[1].spotlight_direction[0] = 0.0;
	LIGHTS[1].spotlight_direction[1] = 0.0;
	LIGHTS[1].spotlight_direction[2] = 1.0;


	LIGHTS[2].position[0] = 0.0;
	LIGHTS[2].position[1] = 0.0;
	LIGHTS[2].position[2] = 100.0;
	LIGHTS[2].position[3] = 1.0;
    LIGHTS[2].color_ambient[0] = 0.0;
    LIGHTS[2].color_ambient[1] = 0.0;
    LIGHTS[2].color_ambient[2] = 0.0;
    LIGHTS[2].color_ambient[3] = 1.0;
    LIGHTS[2].color_diffuse[0] = 0.5;
    LIGHTS[2].color_diffuse[1] = 0.5;
    LIGHTS[2].color_diffuse[2] = 0.5;
    LIGHTS[2].color_diffuse[3] = 1.0;
    LIGHTS[2].color_specular[0] = 0.1;
    LIGHTS[2].color_specular[1] = 0.1;
    LIGHTS[2].color_specular[2] = 0.1;
    LIGHTS[2].color_specular[3] = 1.0;
    LIGHTS[2].attenuation_linear=0.01;
	LIGHTS[2].attenuation_quadratic=0.01;
	LIGHTS[2].spotlight_direction[0] = 0.01;
	LIGHTS[2].spotlight_direction[1] = 0.01;
	LIGHTS[2].spotlight_direction[2] =-1.0;

	/* set up red/green/blue lights */
	GLOBAL.g_lightColor[0] = 1.0f; GLOBAL.g_lightColor[1] = 0.0f; GLOBAL.g_lightColor[2] = 0.0f;
	GLOBAL.g_lightColor[3] = 0.0f; GLOBAL.g_lightColor[4] = 1.0f; GLOBAL.g_lightColor[5] = 0.0f;
	GLOBAL.g_lightColor[6] = 0.0f; GLOBAL.g_lightColor[7] = 0.0f; GLOBAL.g_lightColor[8] = 1.0f;
	GLOBAL.g_lightRotation = 0.0f;

}

GLOBAL_SETTINGS GLOBAL;



void loadShader(){
	printf("loadShader()\n");
	const GLchar* vertexSource = R"glsl(
	    #version 150 core
	    in vec3 position;
	    void main()
	    {
	        gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	    }
	)glsl";
	const GLchar* vertexSource2 = R"glsl(
		varying vec3 N;
		varying vec3 v;

		void main(void)  
		{     
		   v = vec3(gl_ModelViewMatrix * gl_Vertex);       
		   N = normalize(gl_NormalMatrix * gl_Normal);

		   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;  
		})glsl";
	const GLchar* vertexSource3 = R"glsl(
	const int NUM_LIGHTS = 3;

	uniform vec3 cameraPosition;
	uniform vec3 lightPosition[NUM_LIGHTS];

	out vec3 fragmentNormal;
	out vec3 cameraVector;
	out vec3 lightVector[NUM_LIGHTS];
	varying vec2 texture_coordinate;


	void
	main()
	{
		// output the transformed vertex
		gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
		// gl_Position.a = 10;
		// set the normal for the fragment shader and
		// the vector from the vertex to the camera
		fragmentNormal = transpose(inverse(mat3(gl_ModelViewProjectionMatrix))) * gl_Normal ;
		cameraVector = cameraPosition - gl_Position.xyz;

		// set the vectors from the vertex to each light
		for(int i = 0; i < NUM_LIGHTS; ++i)
			lightVector[i] = lightPosition[i] - gl_Position.xyz;


		texture_coordinate = gl_MultiTexCoord0.xy;

	}
				)glsl";

	const GLchar * vertexSource4 = R"glsl(
	// const int NUM_LIGHTS = 3;

	// uniform vec3 cameraPosition;
	// uniform vec3 lightPosition[NUM_LIGHTS];
	varying vec3 normal;
	varying vec4 pos;
	varying vec4 rawpos;
	// varying vec3 lightVector[NUM_LIGHTS];
	// varying vec3 lightVector;

	void main() {
	  normal = gl_NormalMatrix * gl_Normal;
	  gl_Position = ftransform();
	  pos = gl_ModelViewMatrix * gl_Vertex;
	  rawpos = gl_Vertex;
	  gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
	}
	)glsl";

	const GLchar * vertexSource5 = R"glsl(

	const int NUM_LIGHTS = 3;

	uniform vec3 cameraPosition;
	uniform vec3 lightPosition[NUM_LIGHTS];

	out vec3 fragmentNormal;
	out vec3 cameraVector;
	out vec3 lightVector[NUM_LIGHTS];
	varying vec2 texture_coordinate;

	void
	main()
	{
		// set the normal for the fragment shader and
		// the vector from the vertex to the camera
		fragmentNormal = gl_Normal;
		cameraVector = cameraPosition - gl_Vertex.xyz;

		// set the vectors from the vertex to each light
		for(int i = 0; i < NUM_LIGHTS; ++i)
			lightVector[i] = lightPosition[i] - gl_Vertex.xyz;

		// output the transformed vertex
		gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
		texture_coordinate = gl_MultiTexCoord0.xy;
	}
	)glsl";

	const GLchar * vertexSource6 = R"glsl(
	#version 150

	uniform mat4 camera;
	uniform mat4 model;

	in vec3 vert;
	in vec2 vertTexCoord;
	in vec3 vertNormal;

	out vec3 fragVert;
	out vec2 fragTexCoord;
	out vec3 fragNormal;

	void main() {
	    // Pass some variables to the fragment shader
	    fragTexCoord = vertTexCoord;
	    fragNormal = vertNormal;
	    fragVert = vert;
	    
	    // Apply all matrix transformations to vert
	    gl_Position = camera * model * vec4(vert, 1);
	}
	)glsl";
	const GLchar* fragmentSource = R"glsl(
	    #version 150 core
	    out vec4 outColor;
	    void main()
	    {
	        outColor = vec4(1.0, 1.0, 1.0, 1.0);
	        // outColor = outColor;
	    }
	)glsl";
	const GLchar* fragmentSource2 = R"glsl(
	
	varying vec3 fragmentNormal;
	varying vec3 cameraVector; 

	#define MAX_LIGHTS 3 
	// varying lightVector[MAX_LIGHTS]

	void main (void) 
	{ 
	   vec3 N = normalize(fragmentNormal);
	   vec4 finalColor = vec4(0.0, 0.0, 0.0, 0.0);
	   
	   for (int i=0;i<MAX_LIGHTS;i++)
	   {
	      vec3 L = normalize(gl_LightSource[i].position.xyz - cameraVector); 
	      vec3 E = normalize(-cameraVector); // we are in Eye Coordinates, so EyePos is (0,0,0) 
	      vec3 R = normalize(-reflect(L,N)); 
	   
	      //calculate Ambient Term: 
	      vec4 Iamb = gl_FrontLightProduct[i].ambient; 

	      //calculate Diffuse Term: 
	      vec4 Idiff = gl_FrontLightProduct[i].diffuse * max(dot(N,L), 0.0);
	      Idiff = clamp(Idiff, 0.0, 1.0); 
	   
	      // calculate Specular Term:
	      vec4 Ispec = gl_FrontLightProduct[i].specular 
	             * pow(max(dot(R,E),0.0),0.3*gl_FrontMaterial.shininess);
	      Ispec = clamp(Ispec, 0.0, 1.0); 
	   
	      finalColor += Iamb + Idiff + Ispec;
	   }
	   
	   // write Total Color: 
	   gl_FragColor = gl_FrontLightModelProduct.sceneColor + finalColor; 
	}
	          
	)glsl";


	const GLchar* fragmentSource3 = R"glsl(
	const int NUM_LIGHTS = 3;
	const vec3 AMBIENT = vec3(0.0, 0.0, 0.0);
	const float MAX_DIST = 102.5;
	const float MAX_DIST_SQUARED = MAX_DIST * MAX_DIST;

	uniform vec3 lightColor[NUM_LIGHTS];

	in vec3 fragmentNormal;
	in vec3 cameraVector;
	in vec3 lightVector[NUM_LIGHTS];


	void
	main()
	{
		// initialize diffuse/specular lighting
		vec3 diffuse = vec3(0.0, 0.0, 0.0);
		vec3 specular = vec3(0.0, 0.0, 0.0);

		// normalize the fragment normal and camera direction
		vec3 normal = normalize(fragmentNormal);
		vec3 cameraDir = normalize(cameraVector);

		// loop through each light
		for(int i = 0; i < NUM_LIGHTS; ++i) {
			// calculate distance between 0.0 and 1.0
			float dist = min(dot(lightVector[i], lightVector[i]), MAX_DIST_SQUARED) / MAX_DIST_SQUARED;
			float distFactor = 1.0 - dist;

			// diffuse
			vec3 lightDir = normalize(lightVector[i]);
			float diffuseDot = dot(normal, lightDir);
			// float diffuseDot = 1.0;
			diffuse += lightColor[i] * clamp(diffuseDot, 0.0, 1.0)*distFactor;

			// specular
			vec3 halfAngle = normalize(cameraDir + lightDir);
			vec3 specularColor = min(lightColor[i] + 0.5, 1.0);
			float specularDot = dot(normal, halfAngle);
			// specular += specularColor * pow(clamp(specularDot, 0.0, 1.0), 16.0) * distFactor;
		}

		vec4 sample = vec4(1.0, 1.0, 1.0, 1.0);
		gl_FragColor = vec4(clamp(sample.rgb * (diffuse + AMBIENT) + specular, 0.0, 1.0), sample.a);
	}

	)glsl";

	const GLchar* fragmentSource4 = R"glsl(
	const int NUM_LIGHTS = 3;
	uniform vec3 lightPosition[NUM_LIGHTS];
	varying vec3 normal;
	varying vec4 pos;

	void main() {
	  vec4 color = gl_FrontMaterial.diffuse;
	  vec4 matspec = gl_FrontMaterial.specular;
	  float shininess = gl_FrontMaterial.shininess;
	  vec4 lightspec = vec4(0,0,0,0);
	  vec4 lpos = vec4(lightPosition[0],lightPosition[1], lightPosition[2], 0);
	  vec4 s = -normalize(pos-lpos);

	  vec3 light = s.xyz;
	  vec3 n = normalize(normal);
	  vec3 r = -reflect(light, n);
	  r = normalize(r);
	  vec3 v = -pos.xyz;
	  v = normalize(v);
	   
	  vec4 diffuse  = color * max(0.0, dot(n, s.xyz)) * gl_LightSource[0].diffuse;
	  vec4 specular;
	  if (shininess != 0.0) {
	    specular = lightspec * matspec * pow(max(0.0, dot(r, v)), shininess);
	  } else {
	    specular = vec4(0.0, 0.0, 0.0, 0.0);
	  }

	  gl_FragColor = vec4(clamp(diffuse + specular));
	}

	)glsl";
    GLint result;

    const GLchar* fragmentSource5 = R"glsl(
	const int NUM_LIGHTS = 3;
	const vec3 AMBIENT = vec3(0.01, 0.01, 0.01);
	const float MAX_DIST = 102.5;
	const float MAX_DIST_SQUARED = MAX_DIST * MAX_DIST;

	uniform vec3 lightColor[NUM_LIGHTS];
	uniform sampler2D my_color_texture;

	in vec3 fragmentNormal;
	in vec3 cameraVector;
	in vec3 lightVector[NUM_LIGHTS];
	varying vec2 texture_coordinate;

	void
	main()
	{
		// initialize diffuse/specular lighting
		vec3 diffuse = vec3(0.0, 0.0, 0.0);
		vec3 specular = vec3(0.0, 0.0, 0.0);

		// normalize the fragment normal and camera direction
		vec3 normal = normalize(fragmentNormal);
		vec3 cameraDir = normalize(cameraVector);

		// loop through each light
		for(int i = 0; i < NUM_LIGHTS; ++i) {
			// calculate distance between 0.0 and 1.0
			float dist = min(dot(lightVector[i], lightVector[i]), MAX_DIST_SQUARED) / MAX_DIST_SQUARED;
			float distFactor = 1.0 - dist;

			// diffuse
			vec3 lightDir = normalize(lightVector[i]);
			float diffuseDot = dot(normal, lightDir);
			diffuse += lightColor[i] * clamp(diffuseDot, 0.0, 1.0)*distFactor;

			// specular
			vec3 halfAngle = normalize(cameraDir + lightDir);
			vec3 specularColor = min(lightColor[i] + 0.2, 1.0);
			float specularDot = dot(normal, halfAngle);
			// specular += specularColor * pow(clamp(specularDot, 0.0, 1.0), 16.0) * distFactor;
		}

		vec4 sample = texture2D(my_color_texture, texture_coordinate);
		gl_FragColor = vec4(clamp(sample.rgb * (diffuse + AMBIENT) + specular, 0.0, 1.0), sample.a);
		// gl_FragColor = texture2D(my_color_texture, texture_coordinate);
	}

	)glsl";

	const GLchar* fragmentSource6 = R"glsl(
	#version 150

	uniform mat4 model;
	uniform sampler2D tex;

	uniform struct Light {
	   vec3 position;
	   vec3 intensities; //a.k.a the color of the light
	} light;

	in vec2 fragTexCoord;
	in vec3 fragNormal;
	in vec3 fragVert;

	out vec4 finalColor;

	void main() {
	    //calculate normal in world coordinates
	    mat3 normalMatrix = transpose(inverse(mat3(model)));
	    vec3 normal = normalize(normalMatrix * fragNormal);
	    
	    //calculate the location of this fragment (pixel) in world coordinates
	    vec3 fragPosition = vec3(model * vec4(fragVert, 1));
	    
	    //calculate the vector from this pixels surface to the light source
	    vec3 surfaceToLight = light.position - fragPosition;

	    //calculate the cosine of the angle of incidence
	    float brightness = dot(normal, surfaceToLight) / (length(surfaceToLight) * length(normal));
	    brightness = clamp(brightness, 0, 1);

	    //calculate final color of the pixel, based on:
	    // 1. The angle of incidence: brightness
	    // 2. The color/intensities of the light: light.intensities
	    // 3. The texture and texture coord: texture(tex, fragTexCoord)
	    vec4 surfaceColor = texture(tex, fragTexCoord);
	    finalColor = vec4(brightness * light.intensities * surfaceColor.rgb, surfaceColor.a);
	}
	)glsl";

	 // Create and compile the vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource3, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if(result == GL_FALSE) {
		printf("shaderCompile: Unable to compile vertexShader: \n");
		glDeleteShader(vertexShader);
		exit(1);
	}


    // Create and compile the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource5, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE){
    	printf("shaderCompile: Unable to compile fragmentShader: \n");
    	glDeleteShader(fragmentShader);
    	exit(1);
    }

	// printf("Link the vertex and fragment shader into a shader program\n");
    // Link the vertex and fragment shader into a shader program
    GLOBAL.shaderProgram = glCreateProgram();
    glAttachShader(GLOBAL.shaderProgram, vertexShader);
    glAttachShader(GLOBAL.shaderProgram, fragmentShader);
    // glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(GLOBAL.shaderProgram);

    glGetProgramiv(GLOBAL.shaderProgram, GL_LINK_STATUS, &result);
	if(result == GL_FALSE) {
		printf("shader link: Unable to link \n");
		exit(1);
	}
	else{
		printf("Shader linked\n");
	}

/* get uniform locations */
	

	// GLOBAL.baseImageLoc = glGetUniformLocation(GLOBAL.shaderProgram, "my_color_texture");

	

	// createCylinder(36);


	g_cameraPosition[0] = GLOBAL.CAMERA_POS.x;
	g_cameraPosition[1] = GLOBAL.CAMERA_POS.y;
	g_cameraPosition[2] = GLOBAL.CAMERA_POS.z;

	

    // printf("Specify the layout of the vertex data\n");
    // Specify the layout of the vertex data
    // GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    // glEnableVertexAttribArray(posAttrib);
    // glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

   	
	

    // printf("End\n");
}

void loadTex(std::string name){
	if(GLOBAL.TEXTURES_LOADED.count(name) != 0){
		return; //the texture has already been loaded
	}
	struct TextureInfo ti;
	ti.name = name;

	unsigned char * data;

	bool wrap = true;
	// Image im(name);
	// ti.width = im.width();
	// ti.height = im.height();

	glGenTextures(1,(GLuint*)&ti.textureRef); // create the texture space
	glBindTexture(GL_TEXTURE_2D,ti.textureRef);
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE ); // make the color of the polygons and the lighting affect the image

	// when texture area is small, bilinear filter the closest mipmap
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );
	// when texture area is large, bilinear filter the first mipmap
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	// if wrap is true, the texture wraps over at the edges (repeat)
	// false, the texture ends at the edges (clamp)
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap ? GL_REPEAT : GL_CLAMP );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap ? GL_REPEAT : GL_CLAMP );

	//pull the actual image data from the texture
	data = SOIL_load_image(ti.name.c_str(), &ti.width, &ti.height, 0, SOIL_LOAD_RGBA);

	//time to finnally put in our pixel data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ti.width, ti.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	gluBuild2DMipmaps(GL_TEXTURE_2D,4,ti.width,ti.height,GL_RGBA,GL_UNSIGNED_BYTE,data);

	GLOBAL.TEXTURES_LOADED[name]=ti;
	glBindTexture(GL_TEXTURE_2D,0); // reset to the basic texture again
    SOIL_free_image_data(data);

}

void windowResize(int width, int height){

	//move the world cordinates to match the change in the windows draw area
	GLOBAL.WORLD_COORDINATE_MIN_X += 0;
	GLOBAL.WORLD_COORDINATE_MAX_X += width - GLOBAL.WINDOW_MAX_X;
	GLOBAL.WORLD_COORDINATE_MIN_Y += 0;
	GLOBAL.WORLD_COORDINATE_MAX_Y += height - GLOBAL.WINDOW_MAX_Y;

	//remember what the new size of the window is
	GLOBAL.WINDOW_MAX_X = width;
	GLOBAL.WINDOW_MAX_Y = height;

	// glMatrixMode(GL_PROJECTION);
	// glLoadIdentity();
	// gluOrtho2D(WORLD_COORDINATE_MIN_X, WORLD_COORDINATE_MAX_X,  // do the scale again
	//           WORLD_COORDINATE_MIN_Y, WORLD_COORDINATE_MAX_Y);

	//make the scene visable over the whole window
	glViewport(0,0,width,height);
	glutPostRedisplay();
}
void scaleMouse(int &x, int &y){
	y=GLOBAL.WINDOW_MAX_Y-y;

	y*=(GLOBAL.WORLD_COORDINATE_MAX_Y - GLOBAL.WORLD_COORDINATE_MIN_Y) / ((double)GLOBAL.WINDOW_MAX_Y);
	x*=(GLOBAL.WORLD_COORDINATE_MAX_X - GLOBAL.WORLD_COORDINATE_MIN_X) / ((double)GLOBAL.WINDOW_MAX_X);

	y+=GLOBAL.WORLD_COORDINATE_MIN_Y;
	x+=GLOBAL.WORLD_COORDINATE_MIN_X;
}

void cameraMovement(int x, int y, Point center, int cameraMode){
	switch(cameraMode){
		case 0:
			free_CameraMovement(x,y);
			break;
		case 1:
			FPS_CameraMovement(x,y,center);

			break;
		case 2:
			thirdPerson_CameraMovement(x,y,center);
			break;
	}
	
}
void FPS_CameraMovement(int x, int y, Point center){//first person is actually sitting on top of turret
	// bool firstPerson = false;//for rapid testing of different cameras
	double movementDivisor = 3.0;
	//x and y are window cordinates
	//it is up to us to get deltas
	y=GLOBAL.WINDOW_MAX_Y-y;
	int midX = GLOBAL.WINDOW_MAX_X/2;
	int midY = GLOBAL.WINDOW_MAX_Y/2;

	int dx = x-midX;
	int dy = y-midY;
	

	double &angleH = GLOBAL.CAMERA_ANGLE_HORIZONTAL;
	double &angleV = GLOBAL.CAMERA_ANGLE_VERTICAL;
	angleH += dx/movementDivisor;
	if(angleH>360)angleH-=360;
	if(angleH<0)angleH+=360;
	angleV += dy/movementDivisor;
	if(angleV>90)angleV=90;
	if(angleV<-90)angleV=-90;

	
	// we will have a length of 5 for the line in the XY plane
	GLOBAL.CAMERA_LOOK_VECTOR.x = 5 * ( cos(angleH*PI/180.0));
	GLOBAL.CAMERA_LOOK_VECTOR.y = 5 * (-sin(angleH*PI/180.0));
	// make the z from pathagarean formula - our angle is measured from the horizontal plane
	GLOBAL.CAMERA_LOOK_VECTOR.z = 5 * tan(angleV*PI/180.0);
	// GLOBAL.CAMERA_POS.z = 0;

	GLOBAL.CAMERA_POS.x = center.x;
	GLOBAL.CAMERA_POS.y = center.y;
	// GLOBAL.CAMERA_POS.z = center_z + sin(angleV*PI/180.0)+2;
	GLOBAL.CAMERA_POS.z=2;

	if(dx==0 && dy==0)
		return; //we are not really doing anything, so we will simply ignore this thing

	// printf("PassiveFunc\t%dx%d\n",dx,dy); // pixel deltas
	// printf("angles\t%f %f\n",angleH,angleV); // look angles
	// printf("CAMERA_LOOK_VECTOR\t%.2f %.2f %.2f\n",GLOBAL.CAMERA_LOOK_VECTOR.x,GLOBAL.CAMERA_LOOK_VECTOR.y,GLOBAL.CAMERA_LOOK_VECTOR.z); // look vector
	// printf("CAMERA_POS\t%.2f %.2f %.2f\n",GLOBAL.CAMERA_POS.x,GLOBAL.CAMERA_POS.y,GLOBAL.CAMERA_POS.z); // position 

	glutWarpPointer(midX,GLOBAL.WINDOW_MAX_Y-midY);
}

void free_CameraMovement(int x, int y){//move the camera around not bound to the tank
	double movementDivisor = 6.0;
	//x and y are window cordinates
	//it is up to us to get deltas
	y=GLOBAL.WINDOW_MAX_Y-y;
	int midX = GLOBAL.WINDOW_MAX_X/2;
	int midY = GLOBAL.WINDOW_MAX_Y/2;

	int dx = x-midX;
	int dy = y-midY;
	
	double &angleH = GLOBAL.CAMERA_ANGLE_HORIZONTAL;
	double &angleV = GLOBAL.CAMERA_ANGLE_VERTICAL;
	angleH += dx/movementDivisor;
	if(angleH>360)angleH-=360;
	if(angleH<0)angleH+=360;
	angleV += dy/movementDivisor;
	if(angleV>90)angleV=90;
	if(angleV<-90)angleV=-90;

	// we will have a length of 5 for the line in the XY plane
	GLOBAL.CAMERA_LOOK_VECTOR.x = 5 * ( cos(angleH*PI/180.0));
	GLOBAL.CAMERA_LOOK_VECTOR.y = 5 * (-sin(angleH*PI/180.0));
	// make the z from pythagorean formula - our angle is measured from the horizontal plane
	GLOBAL.CAMERA_LOOK_VECTOR.z = 5 * tan(angleV*PI/180.0);

	if(dx==0 && dy==0)
		return; //we are not really doing anything, so we will simply ignore this thing

	glutWarpPointer(midX,GLOBAL.WINDOW_MAX_Y-midY);
}

void thirdPerson_CameraMovement(int x, int y, Point center){//Camera orbits the tank, focused on the tank (over the shoulder view)
	double movementDivisor = 6.0;
	//x and y are window cordinates
	//it is up to us to get deltas
	y=GLOBAL.WINDOW_MAX_Y-y;
	int midX = GLOBAL.WINDOW_MAX_X/2;
	int midY = GLOBAL.WINDOW_MAX_Y/2;

	int dx = x-midX;
	int dy = y-midY;

	double &angleH = GLOBAL.CAMERA_ANGLE_HORIZONTAL;
	double &angleV = GLOBAL.CAMERA_ANGLE_VERTICAL;
	angleH += dx/movementDivisor;
	if(angleH>360)angleH-=360;
	if(angleH<0)angleH+=360;
	angleV += dy/movementDivisor;
	if(angleV>90)angleV=90;
	if(angleV<-20)angleV=-20;

	GLOBAL.CAMERA_POS.x = center.x + 4.0*cos(angleH*PI/180.0);//camera rotates around the center at a radius of 4
	GLOBAL.CAMERA_POS.y = center.y + 4.0*-sin(angleH*PI/180.0);
	GLOBAL.CAMERA_POS.z = ( center.z + sin(angleV*PI/180.0 ) ) +3.0;

	// GLOBAL.CAMERA_LOOK_VECTOR.x = center.x - GLOBAL.CAMERA_POS.x;//look at the center
	// GLOBAL.CAMERA_LOOK_VECTOR.y = center.y - GLOBAL.CAMERA_POS.y;
	// GLOBAL.CAMERA_LOOK_VECTOR.z = center.z - GLOBAL.CAMERA_POS.z +2;
	// double zz = asin()
	GLOBAL.CAMERA_LOOK_VECTOR.x = (center.x+100000)*-cos(angleH*PI/180.0);//circle with radius 1000 - far off focal point
	GLOBAL.CAMERA_LOOK_VECTOR.y = (center.y+100000)*sin(angleH*PI/180.0);
	GLOBAL.CAMERA_LOOK_VECTOR.z = (center.z+100000)*sin(angleV*PI/180.0);

	if(dx==0 && dy==0)
		return; //we are not really doing anything, so we will simply ignore this thing

	glutWarpPointer(midX,GLOBAL.WINDOW_MAX_Y-midY);
}

void drawAxies(){
	static unsigned int listName = 0;
	if(listName!=0){
		glCallList(listName);
	}else{
		listName = glGenLists(1);
		glNewList(listName,GL_COMPILE);

		glBegin(GL_LINES);
			//X
			glColor3ub(255, 0 , 0 );
			glVertex3d(-50,0,0);
			glVertex3d( 50,0,0);
			//Y
			glColor3ub( 0 ,255, 0 );
			glVertex3d(0,-50,0);
			glVertex3d(0, 50,0);
			//Z
			glColor3ub( 0 , 0 ,255);
			glVertex3d(0,0,-50);
			glVertex3d(0,0, 50);
		glEnd();

		// Label our axies
		glColor3ub(255,255,255);

		glPushMatrix();
			glTranslated(10,0,0);
			glScaled(4.0/104.76,4.0/104.76,4.0/104.76);
			glutStrokeCharacter(GLUT_STROKE_ROMAN,'X');
		glPopMatrix();
		glPushMatrix();
			glTranslated(0,10,0);
			glScaled(4.0/104.76,4.0/104.76,4.0/104.76);
			glutStrokeCharacter(GLUT_STROKE_ROMAN,'Y');
		glPopMatrix();
		glPushMatrix();
			glTranslated(0,0,10);
			glScaled(4.0/104.76,4.0/104.76,4.0/104.76);
			glRotated(90,1,0,0);
			glutStrokeCharacter(GLUT_STROKE_ROMAN,'Z');
		glPopMatrix();

		glEndList();
	}

}

void updateLights(){
	// GLfloat temp[]={1.0,1.0,1.0,1.0};
	// glMaterialfv(GL_FRONT,GL_SPECULAR,temp);

	// glLightfv(GL_LIGHT0,GL_POSITION,GLOBAL.LIGHTS[0].position      );
	// glLightfv(GL_LIGHT0,GL_AMBIENT ,GLOBAL.LIGHTS[0].color_ambient );
	// glLightfv(GL_LIGHT0,GL_DIFFUSE ,GLOBAL.LIGHTS[0].color_diffuse );
	// glLightfv(GL_LIGHT0,GL_SPECULAR,GLOBAL.LIGHTS[0].color_specular);
	// glLightf (GL_LIGHT0,GL_LINEAR_ATTENUATION,GLOBAL.LIGHTS[0].attenuation_linear);
	// glLightf (GL_LIGHT0,GL_QUADRATIC_ATTENUATION,GLOBAL.LIGHTS[0].attenuation_quadratic);


	

	// glLightfv(GL_LIGHT1,GL_POSITION,GLOBAL.LIGHTS[1].position      );
	// glLightfv(GL_LIGHT1,GL_AMBIENT ,GLOBAL.LIGHTS[1].color_ambient );
	// glLightfv(GL_LIGHT1,GL_DIFFUSE ,GLOBAL.LIGHTS[1].color_diffuse );
	// glLightfv(GL_LIGHT1,GL_SPECULAR,GLOBAL.LIGHTS[1].color_specular);
	// glLightf (GL_LIGHT1,GL_LINEAR_ATTENUATION,GLOBAL.LIGHTS[1].attenuation_linear);
	// glLightf (GL_LIGHT1,GL_QUADRATIC_ATTENUATION,GLOBAL.LIGHTS[1].attenuation_quadratic);


	
	
	// GLfloat light_2_spot_cutoff = 45.0;
	// GLfloat light_2_spot_exponent = 0;//64

	// glLightfv(GL_LIGHT2,GL_POSITION,GLOBAL.LIGHTS[2].position      );
	// glLightfv(GL_LIGHT2,GL_AMBIENT ,GLOBAL.LIGHTS[2].color_ambient );
	// glLightfv(GL_LIGHT2,GL_DIFFUSE ,GLOBAL.LIGHTS[2].color_diffuse );
	// glLightfv(GL_LIGHT2,GL_SPECULAR,GLOBAL.LIGHTS[2].color_specular);
	// // glLightf (GL_LIGHT2,GL_LINEAR_ATTENUATION,GLOBAL.LIGHTS[2].attenuation_linear);
	// // glLightf (GL_LIGHT2,GL_QUADRATIC_ATTENUATION,GLOBAL.LIGHTS[2].attenuation_quadratic);
	// glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, GLOBAL.LIGHTS[2].spotlight_direction);
	// glLightfv(GL_LIGHT2, GL_SPOT_CUTOFF, &light_2_spot_cutoff);
	// glLightfv(GL_LIGHT2, GL_SPOT_EXPONENT, &light_2_spot_exponent);

    g_cameraPosition[0] = (float)GLOBAL.CAMERA_POS.x;
	g_cameraPosition[1] = (float)GLOBAL.CAMERA_POS.y;
	g_cameraPosition[2] = (float)GLOBAL.CAMERA_POS.z;

 //    g_cameraPosition[0] = (float)GLOBAL.CAMERA_LOOK_VECTOR.x;
	// g_cameraPosition[1] = (float)GLOBAL.CAMERA_LOOK_VECTOR.y;
	// g_cameraPosition[2] = (float)GLOBAL.CAMERA_LOOK_VECTOR.z;
	
	// printf("%f, %f, %f\n",g_cameraPosition[0],g_cameraPosition[1],g_cameraPosition[2]);

	glUniform3fv(GLOBAL.shader_ProgramCameraPositionLocation, 1, g_cameraPosition);
	glUniform3fv(GLOBAL.shader_ProgramLightPositionLocation, NUM_LIGHTS, GLOBAL.g_lightPosition);
	glUniform3fv(GLOBAL.shader_ProgramLightColorLocation, NUM_LIGHTS, GLOBAL.g_lightColor);
	// glUniform1i(GLOBAL.baseImageLoc, 0); //Texture unit 0 is for base images.

}






