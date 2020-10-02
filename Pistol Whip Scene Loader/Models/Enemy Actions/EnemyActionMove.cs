using Newtonsoft.Json;
using System.Collections;
using System.Collections.Generic;
using Unity.Collections;
using UnityEngine;

namespace Models
{
    public class EnemyActionMove : EnemyAction
    {

        public override int actionType { get { return 1; } }


        public WorldPoint destination;

        public Facing facing;

        public enum Facing
        {
            Foward = 0,
            Player = 1,
            Custom = 2
        }
    }
}