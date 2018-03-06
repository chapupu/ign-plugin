/*
 * Copyright (C) 2017 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */


#ifndef IGNITION_COMMON_PLUGINLOADER_HH_
#define IGNITION_COMMON_PLUGINLOADER_HH_

#include <memory>
#include <string>
#include <typeinfo>
#include <unordered_set>

#include <ignition/plugin/loader/Export.hh>

namespace ignition
{
  namespace plugin
  {
    /// \brief Forward declaration
    class LoaderPrivate;
    struct Info;
    class Plugin;

    using PluginPtr = std::shared_ptr<Plugin>;

    /// \brief Class for loading plugins
    class IGNITION_PLUGIN_LOADER_VISIBLE Loader
    {
      /// \brief Constructor
      public: Loader();

      /// \brief Destructor
      public: ~Loader();

      /// \brief Makes a printable string with info about plugins
      /// \returns a pretty string
      public: std::string PrettyStr() const;

      /// \brief get names of interfaces that the loader has plugins for
      /// \returns interfaces that are implemented
      public: std::unordered_set<std::string> InterfacesImplemented() const;

      /// \brief get plugin names that implement the interface
      /// \param[in] _interface name of an interface
      /// \returns names of plugins that implement the interface
      public: std::unordered_set<std::string> PluginsImplementing(
                  const std::string &_interface) const;

      /// \brief Load a library at the given path
      /// \param[in] _pathToLibrary is the path to a libaray
      /// \returns the set of plugins that have been loaded from the library
      public: std::unordered_set<std::string> LoadLibrary(
                  const std::string &_pathToLibrary);

      /// \brief Instantiates a plugin for the given plugin name
      ///
      /// \param[in] _plugin name of the plugin to instantiate
      /// \returns ptr to instantiated plugin
      public: PluginPtr Instantiate(const std::string &_pluginName) const;

      /// \brief Get a pointer to the PluginInfo corresponding to _pluginName.
      /// Returns nullptr if there is no info for the requested _pluginName.
      private: const Info *PrivateGetPluginInfo(
                  const std::string &_pluginName) const;

//      IGN_COMMON_WARN_IGNORE__DLL_INTERFACE_MISSING
      /// \brief PIMPL pointer to class implementation
      private: std::unique_ptr<LoaderPrivate> dataPtr;
//      IGN_COMMON_WARN_RESUME__DLL_INTERFACE_MISSING
    };
  }
}

#endif