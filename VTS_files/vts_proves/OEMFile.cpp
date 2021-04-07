/***********************************************************************************************//**
 *  Creates Orbit Ephemeris Message (OEM) files for the description of position ephemerides.
 *  @class      OEMFile
 *  @author     Eudald Llagostera Brugarola (ELB), eudald.llagostera@estudiantat.upc.edu
 *  @date       2020-dec-6
 *  @copyright  This file is part of a project developed at Nano-Satellite and Payload Laboratory
 *              (NanoSat Lab), Universitat Politècnica de Catalunya - UPC BarcelonaTech.
 **************************************************************************************************/

#include "OEMFile.hpp"

OEMFile::OEMFile(std::string id, std::string m_vts_files_path)
{
    m_vts_sufix = "OEM_POSITION.txt";
    m_id = id; 
    m_cic_name = m_id + m_vts_sufix; 
    m_cic_file.open(m_vts_files_path + "Data/" + m_cic_name);
    m_text = ""; 

    setHeader();
    setMetadata(); 

    m_cic_file.close();
}

void OEMFile::setHeader(void)
{
    m_text = "CIC_OEM_VERS = 2.0\n";
    /* File creation date (e.g. 2009-12-08T09:00:00) */
    time_t now = time(0);
    std::stringstream buffer;
    buffer << std::put_time(gmtime(&now), "%Y-%m-%dT%H:%M:%S");
    m_text += "CREATION_DATE = " + buffer.str() + "\n";
    /** Originator of the file **/
    m_text += "ORIGINATOR = DSS-SIMULATOR\n\n";

    m_cic_file.write(m_text.c_str(), m_text.length());
    m_text = "";
}

void OEMFile::setMetadata(void)
{
    /* Meta-data */
    m_text += "META_START\n";
    /* Name of the object */
    m_text += "OBJECT_NAME = " + m_id + "\n";
    /* Identifier of the object, it is the same than the name */
    m_text += "OBJECT_ID = " + m_id + "\n";
    /* Origin of the reference frame */
    m_text += "CENTER_NAME = EARTH\n";
    /* Reference frame name (mandatory to be 'EME2000') */
    m_text += "REF_FRAME = EME2000\n";
    /* Time system for the file dates */
    m_text += "TIME_SYSTEM = UTC\n";
    /* End of Meta-data */
    m_text += "META_STOP\n\n";

    m_cic_file.write(m_text.c_str(), m_text.length());
    m_text = "";
}

void OEMFile::setData(void)
{
    
}