//
// Copyright (C) 2011-2012 Andrey Sibiryov <me@kobology.ru>
//
// Licensed under the BSD 2-Clause License (the "License");
// you may not use this file except in compliance with the License.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#ifndef COCAINE_HELPERS_PID_FILE_HPP
#define COCAINE_HELPERS_PID_FILE_HPP

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

#include "cocaine/common.hpp"

namespace cocaine { namespace helpers {

class pid_file_t:
    public boost::noncopyable
{
    public:
        pid_file_t(const boost::filesystem::path& filepath):
            m_filepath(filepath)
        {
            // NOTE: If the pidfile exists, check if the process is still active.
            if(boost::filesystem::exists(m_filepath)) {
                pid_t pid;
                boost::filesystem::ifstream stream(m_filepath);

                if(stream) {
                    stream >> pid;

                    if(kill(pid, 0) < 0 && errno == ESRCH) {
                        // NOTE: Unlink the stale pid file.
                        remove();
                    } else {
                        throw std::runtime_error("another instance is active");
                    }
                } else {
                    throw std::runtime_error("failed to read " + m_filepath.string());
                }
            }

            boost::filesystem::ofstream stream(m_filepath);

            if(!stream) {
                throw std::runtime_error("failed to write " + m_filepath.string());
            }

            stream << getpid();
            stream.close();
        }

        ~pid_file_t() {
            try {
                remove();
            } catch(...) {
                // NOTE: Do nothing.
            }
        }

    private:
        inline void remove() {
            try {
                boost::filesystem::remove(m_filepath);
            } catch(const std::runtime_error& e) {
                throw std::runtime_error("failed to remove " + m_filepath.string());
            }
        }

    private:
        const boost::filesystem::path m_filepath;
};

}}

#endif
