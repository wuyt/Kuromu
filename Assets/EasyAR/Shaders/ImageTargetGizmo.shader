//================================================================================================================================
//
//  Copyright (c) 2015-2020 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
//  EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
//  and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//================================================================================================================================

Shader "EasyAR/ImageTargetGizmo"
{
    Properties
    {
        _MainTex ("Texture", 2D) = "white" {}
    }
    SubShader
    {
        Tags { "RenderType"="Opaque" }
        LOD 100
        cull off
        Pass
        {
            CGPROGRAM
            #pragma vertex vert
            #pragma fragment frag
            #pragma multi_compile_fog

            #include "UnityCG.cginc"

            struct appdata
            {
                float4 vertex : POSITION;
                float2 uv : TEXCOORD0;
            };

            struct v2f
            {
                float2 uv : TEXCOORD0;
                UNITY_FOG_COORDS(1)
                float4 vertex : SV_POSITION;
            };

            sampler2D _MainTex;
            float4 _MainTex_ST;
            float4x4 _Transform;
            float _Ratio;
            int _isRenderGrayTexture;

            v2f vert (appdata v)
            {
                v2f o;

                o.uv = TRANSFORM_TEX(v.uv, _MainTex);
                v.vertex.xy = lerp(lerp(float2(0, 1), float2(1, 1), o.uv.x), lerp(float2(0, 0), float2(1, 0), o.uv.x), o.uv.y);
                v.vertex.x = (v.vertex.x - 0.5);
                v.vertex.y = (v.vertex.y - 0.5) * _Ratio;
                v.vertex.z = 0.001;
                v.vertex = mul(_Transform, v.vertex);
                o.vertex = UnityObjectToClipPos(v.vertex);
                return o;
            }

            fixed4 frag (v2f i) : SV_Target
            {
                float2 uv = i.uv;
                fixed4 col;
                if (_isRenderGrayTexture == 1)
                {
                    uv.y = uv.y;
                    col = tex2D(_MainTex, uv).x;
                }
                else
                {
                    uv.y = -uv.y;
                    col = tex2D(_MainTex, uv);

                }
                return col;
            }
            ENDCG
        }
    }
}
