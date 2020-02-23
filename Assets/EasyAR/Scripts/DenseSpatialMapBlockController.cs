//================================================================================================================================
//
//  Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
//  EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
//  and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//================================================================================================================================

using System.Runtime.InteropServices;
using UnityEngine;

namespace easyar
{
    public class DenseSpatialMapBlockController : MonoBehaviour
    {
        public BlockInfo Info { get; private set; }

        private Mesh mesh;
        private Vector3[] vertices;
        private Vector3[] normals;
        private int[] indexes;

        protected virtual void Awake()
        {
            mesh = new Mesh();
        }

        protected virtual void OnDestroy()
        {
            if (mesh)
            {
                Destroy(mesh);
            }
        }

        internal void UpdateData(BlockInfo info, SceneMesh easyarMesh)
        {
            Info = info;

            if (Info.numOfVertex == 0)
            {
                vertices = null;
                normals = null;
                indexes = null;
                gameObject.SetActive(false);
                return;
            }

            gameObject.SetActive(true);
            CopyMeshData(easyarMesh);
        }

        internal void UpdateMesh()
        {
            mesh.Clear();
            mesh.vertices = vertices;
            mesh.normals = normals;
            mesh.SetTriangles(indexes, 0);
            var collider = GetComponent<MeshCollider>();
            if (collider)
            {
                collider.sharedMesh = mesh;
            }
            var filter = GetComponent<MeshFilter>();
            if (filter)
            {
                filter.sharedMesh = mesh;
            }
            vertices = null;
            normals = null;
            indexes = null;
        }

        private void CopyMeshData(SceneMesh easyarMesh)
        {
            using (var verticesBuffer = easyarMesh.getVerticesIncremental())
            using (var normalBuffer = easyarMesh.getNormalsIncremental())
            using (var indicesBuffer = easyarMesh.getIndicesIncremental())
            {
                using (var vb = verticesBuffer.partition(Info.startPointOfVertex * 12, Info.numOfVertex * 12))
                {
                    var vbData = new float[Info.numOfVertex * 3];
                    Marshal.Copy(vb.data(), vbData, 0, vbData.Length);

                    vertices = new Vector3[Info.numOfVertex];
                    for (int i = 0; i < Info.numOfVertex; ++i)
                    {
                        var idx = i * 3;
                        vertices[i] = new Vector3(vbData[idx], vbData[idx + 1], -vbData[idx + 2]);
                    }
                }
                using (var nb = easyarMesh.getNormalsIncremental().partition(Info.startPointOfVertex * 12, Info.numOfVertex * 12))
                {
                    var nbData = new float[Info.numOfVertex * 3];
                    Marshal.Copy(nb.data(), nbData, 0, nbData.Length);

                    normals = new Vector3[Info.numOfVertex];
                    for (int i = 0; i < Info.numOfVertex; ++i)
                    {
                        var idx = i * 3;
                        normals[i] = new Vector3(nbData[idx], nbData[idx + 1], -nbData[idx + 2]);
                    }
                }
                using (var ib = easyarMesh.getIndicesIncremental().partition(Info.startPointOfIndex * 4, Info.numOfIndex * 4))
                {
                    indexes = new int[Info.numOfIndex - Info.numOfIndex % 3];
                    Marshal.Copy(ib.data(), indexes, 0, indexes.Length);

                    for (int i = 2; i < Info.numOfIndex; i += 3)
                    {
                        var tmp = indexes[i];
                        indexes[i] = indexes[i - 1];
                        indexes[i - 1] = tmp;
                    }
                }
            }
        }
    }
}
