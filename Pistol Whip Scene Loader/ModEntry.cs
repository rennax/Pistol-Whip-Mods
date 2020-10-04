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
            static bool firstClick = true;
            public static bool Prefix(SongPanelUIController __instance)
            {
                /* TODO
                - Preview play of song
                */
                MelonLogger.Log($"SongPanelUIController.OnClick called, with level index {__instance.levelDataIndex}");
                if (__instance.levelDataIndex > 19)
                {
                    //if no other song has bee clicked, find the song info panel + start button and enable it
                    if (firstClick)
                    {
                        __instance.parent.startSongUIButton.SetActive(true);
                        GameObject gameObject = GameObject.Find("/Managers/UI State Controller/PF_CHUI_AnchorPt_SongSelection/PF_SongSelectionCanvas_UIv2/PF_SongInfoCanvas_UIv2/PW_VerticalLayoutElementPanel");
                        //MelonLogger.Log(gameObject.name);
                        for (int i = 0; i < gameObject.transform.childCount; i++)
                        {
                            gameObject.transform.GetChild(i).gameObject.SetActive(true);
                            //MelonLogger.Log(i);
                        }
                        firstClick = false;
                    }


                    MelonLogger.Log("Clicked on custom level");
                    Level levelContainer = CustomLevelDatabase.GetLevelAtLevelIndex(__instance.levelDataIndex);
                    Models.LevelData data = levelContainer.data;
                    LevelData level = ConversionExtension.LevelDataNative(data);
                    level.songSwitch = __instance.songSwitch;

                    CustomLevelDatabase.ReplaceSong(levelContainer);

                    //Only make difficulties that actually exist for given map, available to select
                    SongDifficultyUIPanel[] difficultyUIPanels = __instance.parent.difficultyUIPanels;
                    foreach (var difficultyPanel in difficultyUIPanels)
                    {
                        difficultyPanel.isSelectable = false;
                    }

                    foreach (var availableDiff in CustomLevelDatabase.GetDifficultiesForLevel(levelContainer))
                    {
                        difficultyUIPanels[(int)availableDiff].isSelectable = true;
                    }


                    GameManager gm = GameManager.Instance;
                    Difficulty diff = gm.difficulty;
                    GameManager.SetLevel(level.maps[(int)diff]);

                    SongInfoUI songInfo = __instance.parent.songInfoUI;
                    Models.AlbumArtMetadata art = levelContainer.art;
                    songInfo.songTitle.SetText(art.songName);
                    songInfo.songLength.SetText(level.songLength.ToString("0.0"));
                    songInfo.artist.SetText(art.songArtists);
                    songInfo.enemyCount.SetText(level.maps[(int)diff].enemyCount.ToString());
                    songInfo.tempo.SetText(art.tempo); //BPM
                    __instance.parent.lrgAlbumArt.sprite = levelContainer.sprite;

                    //Replace the koreography in WwiseKoreographySets for the koreography to actually be used
                    foreach (var koreo in gm.levels.koreoSets)
                    {
                        foreach (var media in koreo.koreographies)
                        {
                            if (media.mediaID == 561074166) // Religion
                            {
                                //TODO Backup original koreography
                                media.koreo = level.maps[0].trackData.koreography;
                            }
                        }
                    }

                    CustomLevelDatabase.SelectedCustomLevel = true;
                    CustomLevelDatabase.CurrentSelectedLevel = level;

                    return false;
                }
                firstClick = false;
                CustomLevelDatabase.SelectedCustomLevel = false;
                return true;
            }
        }



        [HarmonyPatch(typeof(SongSelectionUIController), "SelectedEasyDifficulty", new System.Type[0])]
        public static class SongSelectionUIController_SelectedEasyDifficulty
        {
            public static bool Prefix(SongSelectionUIController __instance)
            {
                if (CustomLevelDatabase.SelectedCustomLevel)
                {
                    LevelData level = CustomLevelDatabase.CurrentSelectedLevel;
                    GameManager gm = GameManager.Instance;
                    gm.difficulty = Difficulty.Easy;
                    GameManager.SetLevel(level.maps[(int)gm.difficulty]);

                    return false;
                }


                return true;
            }
        }

        [HarmonyPatch(typeof(SongSelectionUIController), "SelectedNormalDifficulty", new System.Type[0])]
        public static class SongSelectionUIController_SelectedNormalDifficulty
        {
            public static bool Prefix(SongSelectionUIController __instance)
            {
                if (CustomLevelDatabase.SelectedCustomLevel)
                {
                    LevelData level = CustomLevelDatabase.CurrentSelectedLevel;
                    GameManager gm = GameManager.Instance;
                    gm.difficulty = Difficulty.Normal;
                    GameManager.SetLevel(level.maps[(int)gm.difficulty]);

                    return false;
                }

                return true;
            }
        }

        [HarmonyPatch(typeof(SongSelectionUIController), "SelectedHardDifficulty", new System.Type[0])]
        public static class SongSelectionUIController_SelectedHardDifficulty
        {
            public static bool Prefix(SongSelectionUIController __instance)
            {
                if (CustomLevelDatabase.SelectedCustomLevel)
                {
                    LevelData level = CustomLevelDatabase.CurrentSelectedLevel;
                    GameManager gm = GameManager.Instance;
                    gm.difficulty = Difficulty.Hard;
                    GameManager.SetLevel(level.maps[(int)gm.difficulty]);

                    return false;
                }

                return true;
            }
        }


    }
}
