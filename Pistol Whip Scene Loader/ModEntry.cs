using MelonLoader;
using System;
using System.Runtime;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;
using UnityEngine.UI;

using UnityEngine.Experimental;

using UnhollowerBaseLib;
using Harmony;
using Newtonsoft.Json;
using Il2CppSystem.Collections.Generic;
using TMPro;
using System.IO;
using SonicBloom.Koreo;

using System.Reflection;
using Il2CppSystem.Reflection;
using Il2CppSystem;
using System.Threading;
using System.Drawing;


/*
TODO List
-   Fix actions and enemy sequence so that they are not enabled by default.
    -   Hook and enable them while playing
        -   only if the current map is a custom map otherwise dont. Original enemy sequences are loaded from asset/resources.
-   Figure out how the rest of the enemy actions work
    -   Some of them refers to animation trigger hashes
-   Fix end of map and exit while playing as this results in just loading a blank world (failed state transition is my guess)
-   TrackSection
    -   Just like enemy actions, write a custom json converter
    -   Write rest of the conversion for track sections
-   Do backup of the koreoset before we overwrite for the custom map
-   Song switch when selection the custom map. Currently this is not done.
-   Figure out how to do props (atleast static ones) without using asset bundles. Keep as much in either our own format or in the json.
-   Write conversion for decor cubes in geoset
-   Figure out what dynamic prop entails. Are they just static props with animations or what?
 */


namespace Pistol_Whip_Scene_Loader
{
    public class ModEntry : MelonMod
    {
        CustomLevelDatabase database = new CustomLevelDatabase();

        public override void OnApplicationStart()
        {
            // Load configuration and overwrite any custom tracks
            MelonLogger.Log("OnApplicationStart called");
            MelonLogger.Log("Initializing custom level database");

            database.RebuildDatabase();
        }



        [HarmonyPatch(typeof(LevelDatabase), "BuildDictionaries", new System.Type[0])]
        public static class LevelDatabase_BuildDictionaries
        {
            
            public static void Postfix(LevelDatabase __instance)
            {
            }
        }
        

        [HarmonyPatch(typeof(SongSelectionUIController), "UpdateSelectedSong", new System.Type[1] { typeof(string) })]
        public static class SongSelectionUIController_SetStartUIPanelState
        {
            public static void Postfix(SongSelectionUIController __instance)
            {

                MelonLogger.Log("SongSelectionUIController.UpdateSelectedSong()");
                CustomLevelDatabase.AddPageIndicators(__instance);
                CustomLevelDatabase.PopulateSongSelectionUI(__instance);
            }
        }

        [HarmonyPatch(typeof(SongSelectionUIController), "Start", new System.Type[0])]
        public static class SongSelectionUIController_Start
        {
            public static void Postfix(SongSelectionUIController __instance)
            {
                MelonLogger.Log("SongSelectionUIController.Start()");
            }
        }


        [HarmonyPatch(typeof(SongPanelUIController), "OnClick", new System.Type[0])]
        public static class SongPanelUIController_OnClick
        {
            public static bool Prefix(SongPanelUIController __instance)
            {
                
                MelonLogger.Log($"SongPanelUIController.OnClick called, with level index {__instance.levelDataIndex}");
                if (__instance.levelDataIndex > 19)
                {
                    MelonLogger.Log("Clicked on custom level");

                    Models.LevelData data = CustomLevelDatabase.GetLevelAtLevelIndex(__instance.levelDataIndex).data;
                    LevelData level = ConversionExtension.LevelDataNative(data);
                    level.songSwitch = __instance.songSwitch;

                    /* TODO
                    - Replace song.wem from custom level folder.
                    - If first song selected
                        - Enable Play button
                        - Enable SongInfoPoster GameObject
                    - Preview play of song

                    */
                    GameManager gm = GameManager.Instance;
                    Difficulty diff = gm.difficulty;
                    GameManager.SetLevel(level.maps[(int)diff]);

                    //Replace the koreography in WwiseKoreographySets for the koreography to actually be used
                    foreach (var koreo in gm.levels.koreoSets)
                    {
                        foreach (var media in koreo.koreographies)
                        {
                            if (media.mediaID == 561074166) // Religion
                            {
                                media.koreo = level.maps[0].trackData.koreography;
                            }
                        }
                    }

                    CustomLevelDatabase.SelectedCustomLevel = true;
                    CustomLevelDatabase.CurrentSelectedLevel = level;

                    return false;
                }

                CustomLevelDatabase.SelectedCustomLevel = false;
                return true;
            }
        }

        public static LevelData CreateLevelInstance(Models.LevelData data)
        {
            LevelData level = ConversionExtension.LevelDataNative(data);



            return level;
        }


    }
}
