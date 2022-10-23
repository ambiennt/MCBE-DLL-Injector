# MCBE DLL Injector
A simple and lightweight Minecraft Bedrock Edition DLL injector

#### Because PC viruses may use simular code to infect computers this might get reconized as a virus. 
#### BUT this injector does not contain any viruses! Feel free to check the source!

## Features:
- Inject any DLL into a UWP process (but defaults to MCBE for Windows)
- Automaticly adds the "All Applications Packages" Permission to the DLL so UWP apps can load it

## Troubleshooting:
VCRUNTIME140_1.dll not found:
1. Go to https://support.microsoft.com/en-us/help/2977003
2. Scroll down and download the x64: vc_redist.x64.exe
3. Run the exe and install it
4. MCBE DLL Injector should open now

#### This project uses [wxWidgets](https://wxwidgets.org).