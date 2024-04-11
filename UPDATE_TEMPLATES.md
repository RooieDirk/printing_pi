# updates-templates README

The script update-templates can be used to update a plugin with
newer versions of the printing templates. The basic workflow
is to

0. If keys exist in the ./ci folder copy them to ./build-deps.
1. Bootstrap process by downloading the updates-templates script
   and add it to repo if it does not exist.
2. Run script
3. Handle updates to CMakeLists.txt/Plugin.cmake
4. Review the flatpak yaml manifest.
5. Upstream local changes to printing templates

## 1.  Bootstrapping

Only required if the update script is not yet part of the repo. Once
installed, the script is self-updating.

### 1.1 Linux and Windows git-bash:

    $ cd some_plugin
    $ repo=https://raw.githubusercontent.com/Rasbats/printing_pi/master
    $ curl $repo/update-templates --output update-templates
    $ chmod 755 update-templates
    $ git add update-templates
    $ git commit -m "Add update-templates script"

It is also possible to use wget instead of curl, like
`wget $repo/update-templates`. Windows works the same way when using git-bash,
except that the `chmod` command does not make sense here and hence is omitted.


### 1.2 Windows (cmd.com)

As in linux, bootstrapping is only required if the script is not yet
available in the plugin repo. Once installed, it's self-updating.

The script is written in bash, so git-bash is required. Using git-bash, the
script can be downloaded and installed as in linux, see above.

Using the Windows command CLI goes like:

    > cd some_plugin
    > set repo=https://raw.githubusercontent.com/Rasbats/printing_pi/master
    > curl %repo%/update-templates --output update-templates
    > git add update-templates
    > git commit -m "Add update-templates script"


## 2. Run script

Before running, commit or stash all changes. The repository must be clean.

The script is run from the plugin top directory using
`./update-templates`. In windows CMD, assuming standard installation paths:

    > "C:\Program Files\Git\bin\bash.exe" update-templates

Usage summary :

    update-templates [-T]  <treeish>
    update-templates <-h|-l>

Parameters:

    treeish:
         A printing tag or branch.  Recommended usage is using the
         latest stable (non-beta) tag.

**-l** lists available tags which can be used as _treeish_

**-T** runs in test mode, lots of output, requires an existing printing 
remote and does not self-update.

**-h** prints the complete help message.

Examples:

    update-templates -l                   -- List available tags
    update-templates sd3.0.2              -- Update from sd3.0.2 tag
    update-templates printing/v3.0      -- Update from v3.0 release branch
    update-templates printing/master    -- Update from development branch


## 3 CMakeLists.txt

As part of the 3.0.0 transition CMakeLists.txt is split into one plugin-specific 
file Plugin.cmake and a generic CMakeLists.txt. If the file _Plugin.cmake_
exists script will thus update _CMakeLists.txt_, otherwise not.

## 4. Checking modifications in flatpak manifest

The "flatpak manifest" is the yaml file configuring the flatpak build,
named like flatpak/org.opencpn.OpenCPN.Plugin.\*.yaml.  This might need
to be updated. If there have been changes to the printing manifest 
since the last release these are added as comments at the end of the
manifest. Review the file, consider applying corresponding changes to
the manifest and eventually remove the comment.


## 5. Upstreaming local changes to printing

If there is a need to modify any of the files updated by update-templates,
please file bugs against the printing repo so the next update runs smoother.

## Testing update-templates

Testing is done using -T which means that many steps otherwise handled
automagically needs to be done manually. This is a complicated and
error-prone procedure.

In  printing repo: Commit changes and create a tag with a sd- prefix, 
something like:

    $ git commit -am "Testing new update-templates"
    $ git tag sd-foo


In client repo, first create the printing remote pointing to the
local printing repository, something like:

    $ git remote add printing ../printing_pi

Still in client repo, import tag and the updated update-templates scripts:

    $ git fetch --no-tags printing refs/tags/sd-foo:refs/tags/sd-foo
    $ git checkout sd-foo update-templates
    $ git commit -am "update-templates: Update to test version"

And run the update:

    $ ./update-templates -T sd-foo
