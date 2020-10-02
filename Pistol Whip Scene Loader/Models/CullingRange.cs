using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
namespace Models
{
    [Serializable]
    public class CullingRange
    {
        public int start;
        public int end;
        public List<WorldObject> members;
    }
}