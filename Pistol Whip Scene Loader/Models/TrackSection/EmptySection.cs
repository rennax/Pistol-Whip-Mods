using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Models
{
    public class EmptySection : TrackSection
    {
        public override int section { get { return 1; } }
        public int laneWidth;
        public bool solidLane;
    }
}