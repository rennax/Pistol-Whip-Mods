using Newtonsoft.Json;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Models
{
    public class EnemyActionStopFiring : EnemyAction
    {
        public override int actionType { get { return 15; } }
    }
}