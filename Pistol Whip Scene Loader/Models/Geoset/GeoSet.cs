﻿using Newtonsoft.Json;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using System;
using System.IO;
using System.Linq;

namespace Models
{
    public class GeoSet
    {
        public Vector3Int chunkSize;

        public float scale;

        public string propsDBName;

        public string chunkDBName;

        public List<ChunkMeshData> chunkData = new List<ChunkMeshData>();
        public List<WorldObject> staticProps = new List<WorldObject>();
    }
}