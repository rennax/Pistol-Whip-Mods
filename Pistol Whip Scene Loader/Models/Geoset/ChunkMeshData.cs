using Newtonsoft.Json;
using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Models
{
    public class ChunkMeshData
    {

        public Vector3i id;

        public Vector3[] verts;

        public int[] meshSizes;

        public int[] tris;

        public Color[] colors;
    }
}