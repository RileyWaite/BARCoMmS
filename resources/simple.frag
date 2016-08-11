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

    //vec3 col = texture2D(myTexture, modifiedTexCoord).xyz;

    //fColor = vec4(col,1.0);
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

    // Normalize coords
    vec2 p = gl_FragCoord.xy / width;

    // screen proportion
    float prop = width / height;

    // center coordinates
    vec2 m = vec2(.5,.5/prop);

    // vector from center to current fragment
    vec2 d = p - m;

    // distance of pixel from center
    float r = sqrt(dot(d, d));

    // amount of effect
    float power = ( 2.0 * 3.1415925 / (2.0 * sqrt(dot(m,m))));

    // radius of 1:1 effect
    float bind;

    if(power > 0.0) bind = sqrt(dot(m,m));
    else if(prop < 1.0) bind = m.x;
    else bind = m.y;

    // Fromulas
    vec2 uv;

    if(power > 0.0) //fisheye
        uv = m + normalize(d) * tan(r*power) * bind / tan(bind*power);
    else if (power < 0.0) //anti-fisheye
        uv = m + normalize(d) * atan(r * -power * 10.0) * bind / atan(-power * bind * 10.0);
    else
        uv = p;

    // Round effect
    modifiedTexCoord = vec2(uv.x, -uv.y * prop);

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
