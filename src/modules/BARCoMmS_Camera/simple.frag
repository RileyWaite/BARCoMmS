#version 330 core

in vec4 vColor;
in vec2 sameTexCoord;
in float sameContrast;
in float sameBrightness;
in float sameWidth;
in float sameHeight;

out vec4 fColor;

uniform sampler2D myTexture;

vec2 fisheyeCorrection(vec2 sameTexCoord, float sameWidth, float sameHeight);
vec2 fisheyeCorrectionEstimate(vec2 sameTexCoord);

void main(void)
{
    //vec2 modifiedTexCoord = fisheyeCorrection(sameTexCoord, sameWidth, sameHeight);
    //vec2 modifiedTexCoord = fisheyeCorrectionEstimate(sameTexCoord);

    fColor = texture2D(myTexture,sameTexCoord);

    // Tint
    fColor.r += vColor.r;
    fColor.g += vColor.g;
    fColor.b += vColor.b;

    // Contrast
    fColor.rgb = (fColor.rgb - 0.5f) * max(sameContrast + 1.0,0) + 0.5f;

    // Brightness
    fColor.rgb += sameBrightness;
}












vec2 fisheyeCorrection(vec2 texCoord, float width, float height)
{
    vec2 modifiedTexCoord;

    // Image Specific Parameters
    float radius = 1;

    float FoV = 180;
    float focalLength = width*height / 3; // f = frameSize / 4 * sin(FoV/4)       FoV = field of view- between 120 and 180 degrees

    // Center of Image (Cx,Cy)
    float Cx = width/2;
    float Cy = height/2;

    // Calculate polar position of pixel
    float k = 1.15;
    float distFromCent = sqrt(abs((sameTexCoord.x-Cx)*(sameTexCoord.x-Cx) + (sameTexCoord.y-Cy)*(sameTexCoord.y*Cy)));
    float R = focalLength * tan(asin(sin(atan(distFromCent/focalLength)*k)));
    float r = focalLength * tan(asin((sin(atan(R/focalLength)))/k));

    float theta = atan(r/focalLength);

    // Output width and height
    //float opw = focalLength * tan(asin(sin(atan((888/2)/focalLength))*k));
    //float oph = focalLength * tan(asin(sin(atan((472/2)/focalLength))*k));

    // Convert back to Cartesian
    modifiedTexCoord.x = r*cos(theta);
    modifiedTexCoord.y = r*sin(theta);


    return modifiedTexCoord;
}

vec2 fisheyeCorrectionEstimate(vec2 sameTexCoord)
{
    vec2 modifiedTexCoord;

    float zoom = 1;
    float radius = 1;
    float pixels = .05;
    // Calc z value of sphere
    float z = sqrt(abs(radius - sameTexCoord.x*sameTexCoord.x - sameTexCoord.y*sameTexCoord.y));

    // Convert to spherical coordinates (distance from origin,longitude,latitude) or (p,phi,theta)
    float p = sqrt(z*z + sameTexCoord.x*sameTexCoord.x + sameTexCoord.y*sameTexCoord.y);
    float longitude = acos(z/p);
    float latitude = asin(sameTexCoord.y/p*sin(longitude));
    // Expand sphere laterally to fit inside of a cylinder
    modifiedTexCoord.x = (128.0f/3.14159f)*pow(2.0f,zoom)*(longitude + 3.14159f)*pixels;
    modifiedTexCoord.y = (128.0f/3.14159f)*pow(2.0f,zoom)*(3.14159f - log(tan(3.14159f/4.0f + latitude/2.0f)))* pixels;

    return modifiedTexCoord;
}
