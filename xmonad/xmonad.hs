import XMonad
import XMonad.Hooks.ManageDocks
import XMonad.Util.Run
import XMonad.Hooks.DynamicLog
import XMonad.Util.CustomKeys
import XMonad.Util.EZConfig

startup :: X ()
startup = do -- Launch app in startup of xmonad
        spawn "redshift -l 49.24:2.48"

main = do
xmproc <- spawnPipe "xmobar"
xmonad $ docks $ defaultConfig
  { terminal = "alacritty"
  , manageHook = manageDocks <+> manageHook defaultConfig
  , layoutHook = avoidStruts $ layoutHook defaultConfig
  , modMask = mod4Mask
  , startupHook = startup
  , focusFollowsMouse = False
  , logHook = dynamicLogWithPP $ defaultPP { ppOutput = hPutStrLn xmproc, ppOrder = \(ws:_:t:_) -> [ws,t] }
  , borderWidth = 3
  } `additionalKeysP` -- All the custom key
  [ ("<XF86MonBrightnessUp>", spawn "xbacklight -inc 5")
  , ("<XF86MonBrightnessDown>", spawn "xbacklight -dec 5")
  , ("M-S-x", spawn "i3lock -c 000000")
  ]
