# Force feedback support for VRS steering wheels

Linux module driver for VRS driving wheels.

VRS wheels are basically DirectInput wheels.
In that repository - copy of pidff driver from 6.6 kernel with some changes around infinite length effects (like that https://github.com/berarma/ffbtools/issues/26)

And that's basically it

## What devices are supported?
### Bases:
1. VRS Driving Force Pro

## What works?
1. FFB (all effects from device descriptor)

## What does not work?
1. Setup through VRS with [some tweaking](#how-to-set-up-a-base-parameters)) (not tested)
2. `Firmware Update` function. Use Windows PC or Windows VM at the moment.

## How to use that driver?
You can install it through DKMS or manually.
### DKMS
1. Install `dkms`
2. Clone repository to `/usr/src/vrs-ff`
3. Install the module: 
`sudo dkms install /usr/src/vrs-ff`
4. Update initramfs:
`sudo update-initramfs -u`
5. Reboot

To remove module:
`sudo dkms remove vrs-ff/<version> --all`
### Manually 

1. Install `linux-headers-$(uname -r)`
2. Clone repository
3. `make`
4. `sudo insmod hid-vrs-ff.ko`

To unload module:
`sudo rmmod hid_vrs_ff`

## How to set up a base parameters?

You can do it through VRS with Wine. You need to tweak Wine prefix for them.

That soft uses hidraw to set up a base. You need to create `udev` rule for allow access to hidraw device:
```
echo 'KERNEL=="hidraw*", ATTRS{idVendor}=="0483", ATTRS{idProduct}=="a355", MODE="0666", TAG+="uaccess"' | sudo tee /etc/udev/rules.d/11-vrs.rules

udevadm control --reload-rules && udevadm trigger
```

Then you need to force VRS soft to use hidraw, not SDL, to find devices:
1. Create new Wine prefix for them:

      `mkdir ~/vrs-wine`
2. Launch regedit in prefix:

      `WINEPREFIX=$HOME/vrs-wine wine regedit`
3. Create two keys in
  `HKEY_LOCAL_MACHINE\System\CurrentControlSet\Services\winebus`:

    * `DisableInput` (DWORD) - set to `1`;
    * `Enable SDL` (DWORD) - set to `0`; (yes, variable name contains  space)
4. Now you can launch soft through that WINEPREFIX:

    `WINEPREFIX=$HOME/vrs-wine wine VRS.exe` - launch your soft from installation directory.

## Known issues with the driver
1. Firmware update does not work. Please use Windows machine or Windows VM for any firmware updates

## Known issues with the firmware 
You tell me please

## DISCLAIMER
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
