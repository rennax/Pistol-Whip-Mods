using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Pistol_Whip_Scene_Loader.Conversion
{
    public class TrackSectionConverter : JsonConverter
    {
        public override bool CanConvert(Type objectType)
        {
            return typeof(Models.EnemyAction).IsAssignableFrom(objectType);
        }

        public override object ReadJson(JsonReader reader,
            Type objectType, object existingValue, JsonSerializer serializer)
        {
            JObject j = JObject.Load(reader);

            // Using a nullable bool here in case "is_album" is not present on an item
            int? section = (int?)j["section"];

            Models.TrackSection action = null;
            switch (section)
            {
                case 0:
                    action = new Models.FilledSection();
                    break;
                case 1:
                    action = new Models.EmptySection();
                    break;
                case 2:
                    action = new Models.AlleySection();
                    break;
                case 3:
                    action = new Models.RoomSection();
                    break;
                case 4:
                    action = new Models.HallwaySection();
                    break;
                case 5:
                    action = new Models.OfficeSection();
                    break;
                case 6:
                    action = new Models.GroundSection();
                    break;
                case 7:
                    action = new Models.RooftopSection();
                    break;
                case 8:
                    action = new Models.SplitRooftopSection();
                    break;
            }

            serializer.Populate(j.CreateReader(), action);

            return action;
        }

        public override bool CanWrite
        {
            get { return false; }
        }

        public override void WriteJson(JsonWriter writer,
            object value, JsonSerializer serializer)
        {
            throw new NotImplementedException();
        }
    }
}
