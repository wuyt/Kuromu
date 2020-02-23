//================================================================================================================================
//
//  Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
//  EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
//  and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//================================================================================================================================

Shader "EasyAR/DenseSpatialMapMesh"
{
    Properties
    {
        _Color("MeshColor", Color) = (1,1,1,1)
        _MeshDense("MeshDense", Range(0.01,1)) = 0.1
        _CriticalValue("CriticalValue", Range(0,1)) = 0.8
        _Shininess("Shininess", Range(1,10)) = 1
        _SpeColor("SpeColor", color) = (1,1,1,1)
        _DepthTexture("DepthTexture", 2D) = "withe"{}
        _MainTexture("MainTexture", 2D) = "withe"{}
    }

    SubShader
    {
        Tags {  "Tag" = "DenseSpatialMap" "LightMode" = "ForwardBase" }

        Pass
        {
            Blend SrcAlpha OneMinusSrcAlpha
            ZWrite On
            CGPROGRAM
            #pragma vertex vert
            #pragma fragment frag
            #include "UnityCG.cginc"
            #include "Lighting.cginc"
            #pragma multi_compile_fwdbase nolightmap nodirlightmap nodynlightmap novertexlight
            #include "AutoLight.cginc"

            fixed _MeshDense;
            fixed _CriticalValue;
            fixed _Shininess;

            fixed4 _Color;
            fixed4 _SpeColor;
            fixed4 _MainTex_TexelSize;

            sampler2D_float _DepthTexture;
            sampler2D _MainTexture;

            struct appdata
            {
                float4 vertex : POSITION;
                half3 normal : NORMAL;
            };

            struct v2f
            {
                float4 pos : SV_POSITION;
                float4 uv : TEXCOORD0;
                SHADOW_COORDS(1)
                float3 normal : NORMAL;
                float4 worldPos : COLOR0;
                float4 viewPos : COLOR1;
                float3 diff : COLOR2;
                fixed3 ambient : COLOR3;
            };

            v2f vert(appdata v)
            {
                v2f o;
                UNITY_INITIALIZE_OUTPUT(v2f, o);
                o.worldPos = mul(UNITY_MATRIX_M, v.vertex);
                o.viewPos = mul(UNITY_MATRIX_V, o.worldPos);
                o.pos = mul(UNITY_MATRIX_P, o.viewPos);
                o.uv = ComputeGrabScreenPos(o.pos);
                o.normal = UnityObjectToWorldNormal(v.normal);
                half nl = max(0.0, dot(o.normal, _WorldSpaceLightPos0.xyz));
                nl = pow(nl, _Shininess);
                o.diff = nl;
                o.ambient = ShadeSH9(half4(o.normal, 1));
                TRANSFER_SHADOW(o)
                return o;
            }

            fixed4 frag(v2f i) : SV_Target
            {

                float2 uv = i.uv.xy / i.uv.w;
#if UNITY_UV_STARTS_AT_TOP
                uv.y = 1.0 - uv.y;
#endif
                float4 depth_rgba = tex2D(_DepthTexture, uv);
                float depth = DecodeFloatRGBA(depth_rgba);

                if (length(i.viewPos.xyz) * 0.000001 - depth >= 0.005 * 0.000001)
                {
                    discard;
                }
                float3 posUV = float3(abs(i.worldPos.x % _MeshDense), abs(i.worldPos.y % _MeshDense), abs(i.worldPos.z % _MeshDense)) / _MeshDense;

                fixed4 color = _Color;
                fixed4 texColor = fixed4(0.0, 0.0, 0.0, 0.0);
                if (abs(dot(normalize(i.normal), float3(1.0, 0.0, 0.0))) >= _CriticalValue)
                {
                    texColor = tex2D(_MainTexture, posUV.zy);
                }
                else if (abs(dot(i.normal, float3(0.0, 1.0, 0.0))) >= _CriticalValue)
                {
                    texColor = tex2D(_MainTexture, posUV.xz);
                }
                else if (abs(dot(i.normal, float3(0.0, 0.0, 1.0))) >= _CriticalValue)
                {
                    texColor = tex2D(_MainTexture, posUV.xy);
                }

                color.rgb += texColor.rgb * texColor.a;
                fixed shadow = SHADOW_ATTENUATION(i);

                color.rgb *= _SpeColor.rgb * i.diff * shadow + i.ambient;

                return color;
            }
            ENDCG
        }

        UsePass "Legacy Shaders/VertexLit/SHADOWCASTER"
    }
}
