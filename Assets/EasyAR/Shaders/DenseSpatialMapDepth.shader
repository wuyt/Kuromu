//================================================================================================================================
//
//  Copyright (c) 2015-2020 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
//  EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
//  and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//================================================================================================================================

Shader "EasyAR/DenseSpatialMapDepth" {

    SubShader
    {
        Tags { "Tag" = "DenseSpatialMap" }

        Pass {

            CGPROGRAM

            #pragma vertex vert
            #pragma fragment frag
            #include "UnityCG.cginc"

            struct v2f
            {
                float4 pos : SV_POSITION;
                float4 depthPos : TEXCOORD0;
            };

           v2f vert(appdata_base v)
            {
                v2f o;
                o.depthPos.xyz = UnityObjectToViewPos(v.vertex);
                o.depthPos.w = 1.0;
                o.pos = mul(UNITY_MATRIX_P, o.depthPos);
                return o;
            }

            float4 frag(v2f i) : SV_Target {
                float depth = length(i.depthPos.xyz);
                depth = depth * 0.000001;
                return EncodeFloatRGBA(depth);
            }
            ENDCG
        }
    }
}