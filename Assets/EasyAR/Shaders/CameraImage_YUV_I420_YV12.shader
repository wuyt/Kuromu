//================================================================================================================================
//
//  Copyright (c) 2015-2020 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
//  EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
//  and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//================================================================================================================================

Shader "EasyAR/CameraImage_YUV_I420_YV12"
{
    Properties
    {
        _yTexture("Texture", 2D) = "white" {}
        _uTexture("Texture", 2D) = "white" {}
        _vTexture("Texture", 2D) = "white" {}
    }
        SubShader
    {
        Tags { "RenderType" = "Opaque" }
        LOD 100

        Pass
        {
            Cull Off
            ZWrite Off
            CGPROGRAM
            #pragma vertex vert
            #pragma fragment frag
            #include "UnityCG.cginc"

            struct appdata
            {
                float4 vertex : POSITION;
                float2 uv : TEXCOORD0;
            };

            struct v2f
            {
                float2 uv : TEXCOORD0;
                float4 vertex : SV_POSITION;
            };

            sampler2D _yTexture;
            float4 _yTexture_ST;
            sampler2D _uTexture;
            sampler2D _vTexture;
            float4x4 _TextureRotation;

            v2f vert(appdata v)
            {
                v2f o;
                o.vertex = UnityObjectToClipPos(v.vertex);
                o.uv = TRANSFORM_TEX(v.uv, _yTexture);
                o.uv = float2(o.uv.x, 1.0 - o.uv.y);
                o.vertex = mul(_TextureRotation, o.vertex);
                return o;
            }

            fixed4 frag(v2f i) : SV_Target
            {
                const float4x4 ycbcrToRGBTransform = float4x4(
                    float4(1.0, +0.0000, +1.4020, -0.7010),
                    float4(1.0, -0.3441, -0.7141, +0.5291),
                    float4(1.0, +1.7720, +0.0000, -0.8860),
                    float4(0.0, +0.0000, +0.0000, +1.0000)
                    );
                float2 texcoord = i.uv;
                float y = tex2D(_yTexture, texcoord).a;
                float cb = tex2D(_uTexture, i.uv).a;
                float cr = tex2D(_vTexture, i.uv).a;
                float4 ycbcr = float4(y, cb, cr, 1.0);
                return mul(ycbcrToRGBTransform, ycbcr);
            }
            ENDCG
        }
    }
}
