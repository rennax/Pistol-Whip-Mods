using Newtonsoft.Json;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Models
{
    public class WorldObject
    {

        public WorldPoint point;
        //Dont serialize prefabObj, it is saved to assetbundle
        //public GameObject prefabObj;

        public Vector3 scale;

        //Prefab is saved to "props" asset bundle
        //Thus we just save the name and load it from that
        public string prefab;
    }
}